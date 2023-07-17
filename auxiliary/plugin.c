#include "oio_sds.h"
#include "oio_core.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static const gchar* _ns_ = "OPENIO";

struct oio_url_s* create_empty_url() {
    struct oio_url_s* url = oio_url_empty();
    g_assert_nonnull(url);
    return url;
}

void basic_init(struct oio_url_s* url, const gchar* user, const gchar* path) {
    oio_url_set(url, OIOURL_NS, _ns_);

    if (user != NULL) {
        oio_url_set(url, OIOURL_USER, user);
    }
    
    if (path != NULL) {
        oio_url_set(url, OIOURL_PATH, path);
    }
}

void clean_up(struct oio_sds_s* client, gchar* path) {
    struct oio_error_s* err = NULL;

    struct oio_url_s* url = create_empty_url();
    basic_init(url, path, NULL);

    struct oio_sds_list_param_s list_in = {
        .url = url,
        .prefix = NULL, .marker = NULL, .end = NULL, .delimiter = 0, .max_items = 0,
        .flag_allversions = 1, .flag_nodeleted = 1, .flag_properties = 1
    };

    int _delete_item(void* ctx, const struct oio_sds_list_item_s* item) {
        (void) ctx;
        g_print("Deleting item: %s...\n", item->name);

        struct oio_url_s* tmp_url = create_empty_url();
        basic_init(tmp_url, path, item->name);

        err = oio_sds_delete(client, tmp_url);
        oio_url_clean(tmp_url);
        g_assert_no_error((GError*)err);
    }

    struct oio_sds_list_listener_s list_out = {
        .ctx = NULL,
        .on_item = _delete_item, .on_prefix = NULL, .on_bound = NULL
    };

    err = oio_sds_list(client, &list_in, &list_out);
    oio_url_clean(url);
    g_assert_no_error((GError*)err);

    url = create_empty_url();
    basic_init(url, path, NULL);
    
    err = oio_sds_delete_container(client, url);
    g_assert_no_error((GError*)err);
    oio_url_clean(url);
}

struct JBackendData {
    struct oio_sds_s* client;
    gchar* user; // container name
};

typedef struct JBackendData JBackendData;

struct JBackendIterator {
    /* ?? some list items probably ?? */
};

typedef struct JBackendIterator JBackendIterator;

struct JBackendObject {
    struct oio_url_s* url;
};

typedef struct JBackendObject JBackendObject;

static guint jd_num_backends = 0;

// TODO: what if the file with this path already exists
// seems like semantics of this function was not understood properly
static gboolean
backend_create(gpointer backend_data, gchar const* namespace,
               gchar const* path, gpointer* backend_object) {
    struct oio_error_s* err = NULL;

    JBackendData* bd = (JBackendData*)backend_data;
    JBackendObject* bo = g_slice_new(JBackendObject);
    
    struct oio_url_s* url = create_empty_url(); // future backend_object
    basic_init(url, bd->user, path);

    // fill the url with empty content in order to create an object
    struct oio_sds_ul_dst_s ul_dst = OIO_SDS_UPLOAD_DST_INIT;
    ul_dst.url = url;
    gchar content[] = "";
    
    err = oio_sds_upload_from_buffer(bd->client, &ul_dst, content, 0);
    g_assert_no_error((GError*)err);

    bo->url = url;

    return TRUE;
}

static gboolean
backend_open(gpointer backend_data, gchar const* namespace,
             gchar const* path, gpointer* backend_object) {
    /* does nothing ... */
}

// may be different behavior for objects and containers
static gboolean
backend_delete(gpointer backend_data, gpointer backend_object) {
    struct oio_error_s* err = NULL;

    JBackendData* bd = (JBackendData*)bd;
    JBackendObject* bo = (JBackendObject*)bo;


    err = oio_sds_delete(bd->client, bo->url);
    g_assert_no_error((GError*)err); // should be removed!
    return (err == NULL);
}

static gboolean
backend_close(gpointer backend_data, gpointer backend_object) {
    /* does nothing */
}

static gboolean
backend_status(gpointer backend_data, gpointer backend_object,
               guint64* modification_time, guint64* size) {
    struct oio_error_s* err = NULL;

    JBackendData* bd = (JBackendData*)bd;
    JBackendObject* bo = (JBackendObject*)bo;

    void _oio_sds_info_reporter_size(void* cb_data,
                                     enum oio_sds_content_key_e key,
                                     const char* value){
        if (key == OIO_SDS_CONTENT_SIZE) {
            sscanf(value, "%zu", (guint64*)cb_data);
        }
    }

    err = oio_sds_show_content(bd->client, bo->url, (void*)size,
                               _oio_sds_info_reporter_size, NULL, NULL);
    g_assert_no_error((GError*)err);

}

static gboolean
backend_sync(gpointer backend_data, gpointer backend_object) {

}

static gboolean
backend_read(gpointer backend_data, gpointer backend_object,
             gpointer buffer,
             guint64 length, guint64 offset,
             guint64* bytes_read) {
    struct oio_error_s* err = NULL;

    JBackendData* bd = (JBackendData*)backend_data;
    JBackendObject* bo = (JBackendObject*)backend_object;

    guint64 total = 0;

    while (total < length) {
        struct oio_sds_dl_range_s range = { .offset = offset, .size = length };
 
        struct oio_sds_dl_range_s* ranges_arr[2];
        ranges_arr[0] = &range;
        ranges_arr[1] = NULL;
 
        struct oio_sds_dl_src_s src = { .url = bo->url, .ranges = ranges_arr };
        struct oio_sds_dl_dst_s dst = { .type = OIO_DL_DST_BUFFER, 
                                        .data = { .buffer = 
                                                { .ptr = buffer, .length = length} } 
        };
 
        err = oio_sds_download(bd->client, &src, &dst);
        g_assert_no_error((GError*)err);

        if (dst.out_size == 0) {
            break;
        }

        total += dst.out_size;
    
    }

    *bytes_read = total;

    return (*bytes_read == length);
}

static gboolean
backend_write(gpointer backend_data, gpointer backend_object,
              gconstpointer buffer,
              guint64 length, guint64 offset,
              guint64* bytes_written) {

}

static gboolean
backend_get_all(gpointer backend_data, gchar const* namespace,
                gpointer* backend_iterator) {

}

static gboolean
backend_get_by_prefix(gpointer backend_data, gchar const* namespace,
                      gchar const* prefix, gpointer* backend_iterator) {

}

static gboolean
backend_iterate(gpointer backend_data, gpointer backend_iterator,
                gchar const** name) {

}

static gboolean
backend_init(gchar const* path, gpointer* backend_data) {
    struct oio_error_s* err = NULL;

    JBackendData* bd;
    bd = g_slice_new(JBackendData);

    bd->user = g_strdup(path);
    bd->client = NULL;

    err = oio_sds_init(&(bd->client), _ns_);
    g_assert_no_error((GError*)err);

    // need to create a container
    struct oio_url_s* url = create_empty_url();
    basic_init(url, path, NULL);
    err = oio_sds_create(bd->client, url);
    g_assert_no_error((GError*)err);
    oio_url_clean(url);

    *backend_data = bd;

    return TRUE;
}

static void
backend_fini(gpointer backend_data) {
    struct oio_error_s* err = NULL;

    JBackendData* bd = (JBackendData*)backend_data;

    // need to delete current container
    clean_up(bd->client, bd->user);

    g_free(bd->user);
    g_slice_free(JBackendData, bd);
}

int main()  {
    
}
