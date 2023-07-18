#include "oio_sds.h"
#include "oio_core.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static const gchar* _ns_ = "OPENIO";
static const gchar* _account_ = "ACCOUNT";

struct oio_url_s* create_empty_url() {
     struct oio_url_s* url = oio_url_empty();
     g_assert_nonnull(url);
     return url;
 }

 void basic_init(struct oio_url_s* url, const gchar* user, const gchar* path) {
     oio_url_set(url, OIOURL_NS, _ns_);
     oio_url_set(url, OIOURL_ACCOUNT, _account_);

     if (user != NULL) {
         oio_url_set(url, OIOURL_USER, user);
     }

     if (path != NULL) {
         oio_url_set(url, OIOURL_PATH, path);
     }
 }

struct JBackendIterator {
    char* marker;
    char* prefix;
};

typedef struct JBackendIterator JBackendIterator;

JBackendIterator* iterator_new(const char* prefix) {
    JBackendIterator* it = g_slice_new(JBackendIterator);

    it->marker = g_strdup("");
    it->prefix = (prefix == NULL) ? NULL : g_strdup(prefix);

    return it;
}

void iterator_free(JBackendIterator* it) {
    if (it->marker != NULL) {
        g_free(it->marker);
    }

    if (it->prefix != NULL) {
        g_free(it->prefix);
    }

    g_slice_free(JBackendIterator, it);

    
}

void iterator_next(struct oio_sds_s* client, struct oio_error_s* err,
                   JBackendIterator* it,
                   const char* prefix,
                   const char* container) {
    struct oio_url_s* url = create_empty_url();
    basic_init(url, container, NULL);

    struct oio_sds_list_param_s list_in = {
        .url = url,
        .prefix = prefix, .marker = it->marker, .end = NULL, .delimiter = 0,
        .max_items = 1,
        .flag_allversions = 1, .flag_nodeleted = 1, .flag_properties = 1
    };

    gchar marker[256];

    int _process_item(void* ctx, const struct oio_sds_list_item_s* item) {
        (void)ctx;
        g_strlcpy(marker, item->name, 256);
        // after that marker contains name of current item also!
        return 0;
    }

    struct oio_sds_list_listener_s list_out = {
        .ctx = NULL,
        .on_item = _process_item, .on_prefix = NULL, .on_bound = NULL
    };

    err = oio_sds_list(client, &list_in, &list_out);
    g_assert_no_error((GError*)err);

    g_free(it->marker);

    if (list_out.out_count <= 0) {
        it->marker = NULL;
        return;
    }

    it->marker = g_strdup(marker);
}

char* iterator_get(JBackendIterator* it) {
    if (it == NULL) {
        return NULL;
    }
    return it->marker;
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

void show_info(struct oio_sds_s* client, struct oio_error_s* err,
               struct oio_url_s* url) {
    g_print("OIOURL_NS: %s\n", oio_url_get(url, OIOURL_NS));
    g_print("OIOURL_ACCOUNT: %s\n", oio_url_get(url, OIOURL_ACCOUNT));
    g_print("OIOURL_USER: %s\n", oio_url_get(url, OIOURL_USER));
    g_print("OIOURL_PATH: %s\n", oio_url_get(url, OIOURL_PATH));
    g_print("OIOURL_VERSION: %s\n", oio_url_get(url, OIOURL_VERSION));
    g_print("OIOURL_WHOLE: %s\n", oio_url_get(url, OIOURL_WHOLE));
    g_print("OIOURL_HEXID: %s\n", oio_url_get(url, OIOURL_HEXID));
    g_print("OIOURL_CONTENTID: %s\n", oio_url_get(url, OIOURL_CONTENTID));
    g_print("OIOURL_FULLPATH: %s\n", oio_url_get(url, OIOURL_FULLPATH));
}



void show_content(struct oio_sds_s* client, struct oio_error_s* err,
                  struct oio_url_s* url) {
    const char* name = oio_url_get(url, OIOURL_PATH);

    guchar data[1024];
    memset(data, 0, 1024);
    struct oio_sds_dl_src_s src = { .url = url, .ranges = NULL };
    struct oio_sds_dl_dst_s dst = { .type = OIO_DL_DST_BUFFER,
                        .data = { .buffer = { .ptr = data, .length = sizeof(data) } }
    };
    err = oio_sds_download(client, &src, &dst);
    g_assert_no_error((GError*)err);

    g_print("Content of `%s`: %s\n", name, data);
}

struct JBackendData {
    struct oio_sds_s* client;
    gchar* user; // container name
};

typedef struct JBackendData JBackendData;

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
    
    err = oio_sds_upload_from_buffer(bd->client, &ul_dst, content, 1);
    g_assert_no_error((GError*)err);

    bo->url = url;

    *backend_object = bo;

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

    JBackendData* bd = (JBackendData*)backend_data;
    JBackendObject* bo = (JBackendObject*)backend_object;


    err = oio_sds_delete(bd->client, bo->url);
    g_assert_no_error((GError*)err); // should be removed!
    return (err == NULL);
}

static gboolean
backend_close(gpointer backend_data, gpointer backend_object) {
    /* does nothing */
}

void get_size(struct oio_sds_s* client, struct oio_error_s* err,
              struct oio_url_s* url,
              guint64* size) {
    void _oio_sds_info_reporter_size(void* cb_data,
                                     enum oio_sds_content_key_e key,
                                     const char* value){
        if (key == OIO_SDS_CONTENT_SIZE) {
            sscanf(value, "%zu", (guint64*)cb_data);
        }
    }

    err = oio_sds_show_content(client, url, (void*)size,
                               _oio_sds_info_reporter_size, NULL, NULL);
    g_assert_no_error((GError*)err);
}

static gboolean
backend_status(gpointer backend_data, gpointer backend_object,
               guint64* modification_time, guint64* size) {
    struct oio_error_s* err = NULL;

    JBackendData* bd = (JBackendData*)backend_data;
    JBackendObject* bo = (JBackendObject*)backend_object;

    get_size(bd->client, err, bo->url, size);
}

static gboolean
backend_sync(gpointer backend_data, gpointer backend_object) {
    /* does nothing...  */
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
    if (offset != 0) return FALSE; // TODO: what if offset is not equal to 0? 

    struct oio_error_s* err= NULL;

    JBackendData* bd = (JBackendData*)backend_data;
    JBackendObject* bo = (JBackendObject*)backend_object;

    show_info(bd->client, err, bo->url);
    fflush(stdout);

    struct oio_sds_ul_dst_s ul_dst = OIO_SDS_UPLOAD_DST_INIT;
    ul_dst.url = bo->url;

    err = oio_sds_upload_from_buffer(bd->client, &ul_dst, buffer, length);
    g_assert_no_error((GError*)err);

    g_print("wrote %ld bytes\n", ul_dst.out_size);
    *bytes_written = ul_dst.out_size; // does not give expected result :(

    return (ul_dst.out_size == length);
}

static gboolean
backend_get_all(gpointer backend_data, gchar const* namespace,
                gpointer* backend_iterator) {
    (void)namespace;
    (void)backend_data;
    
    JBackendIterator* bi = iterator_new(NULL);

    *backend_iterator = (void*)bi;

    return TRUE;
}

static gboolean
backend_get_by_prefix(gpointer backend_data, gchar const* namespace,
                      gchar const* prefix, gpointer* backend_iterator) {
    (void)namespace;
    (void)backend_data;

    JBackendIterator* bi = iterator_new(prefix);

    *backend_iterator = (void*)bi;

    return TRUE;
}

static gboolean
backend_iterate(gpointer backend_data, gpointer backend_iterator,
                gchar** name) {
    struct oio_error_s* err = NULL;

    JBackendData* bd = (JBackendData*)backend_data;
    JBackendIterator* bi = (JBackendIterator*)backend_iterator;

    iterator_next(bd->client, err, bi, bi->prefix, bd->user);

    if (name != NULL) {
        *name = iterator_get(bi);
    }

    return (*name != NULL);
}

static gboolean
backend_init(gchar const* path, gpointer* backend_data) {
    struct oio_error_s* err = NULL;

    JBackendData* bd;
    bd = g_slice_new(JBackendData);

    bd->user = g_strdup(path);
    bd->client = NULL;

    struct oio_sds_s* client = NULL;

    err = oio_sds_init(&client, _ns_);
    g_assert_no_error((GError*)err);

    // need to create a container
    struct oio_url_s* url = create_empty_url();
    basic_init(url, path, NULL);
    err = oio_sds_create(client, url);
    g_assert_no_error((GError*)err);
    oio_url_clean(url);

    bd->client = client;
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


/*
 *
 *
 * Here you can find some test
 * to ensure that written plugin really works somehow
 *
 *
 *
 *
 *
 * Tests will be removed from final version of the code
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

void short_test() {
    // shows that easy functions really work
    struct oio_error_s* err = NULL;
    JBackendData* bd = NULL;

    backend_init("new_container", (void**)&bd);

    JBackendObject* bo = NULL;
    gboolean flag  = backend_create(bd, "OPENIO", "obj", (void**)&bo);
    if (flag) g_print("Success on creating!\n");

    char buffer[] = "Sample content";
    guint64 cnt = 0;

    flag = backend_write((void*)bd, (void*)bo,
                         (void*)buffer,
                         strlen(buffer) + 1, 0, &cnt);
    show_content(bd->client, err, bo->url);
    g_print("%ld bytes written\n", cnt);

    char buff[256];
    flag = backend_read((void*)bd, (void*)bo,
                        (void*)buff,
                        strlen(buffer) - 1, 2, &cnt);
    g_print("Read %ld bytes: %s\n", cnt, buff);

    guint64 modification_time = 0;
    guint64 size = 0;

    //get_size(bd->client, err, bo->url, &size);
    backend_status((void*)bd, (void*)bo, &modification_time, &size);
    g_print("modification time: %ld, size: %ld\n", modification_time, size);

    backend_delete((void*)bd, (void*)bo);

    backend_fini((void*)bd);
}

void fill_container(JBackendData* bd) {
    struct oio_error_s* err = NULL;

    gboolean flag;

    gchar data[] = "Sample";
    gchar foo[] = "foo/_";
    size_t foo_pos = strlen(foo) - 1;
    gchar object[] = "obj_";
    size_t object_pos = strlen(object) - 1;

    guint64 cnt;

    for (char i = 'a'; i < 'e'; ++i) {
        foo[foo_pos] = i;

        JBackendObject* bo = NULL;
        flag = backend_create(bd, "OPENIO", foo, (void**)&bo);
        if (!flag) g_print("Error on creating :(\n");
        // we don't need to fill objects with smth at this point
    }

    for (char i = '0'; i < '5'; ++i) {
        object[object_pos] = i;

        JBackendObject* bo = NULL;
        flag = backend_create(bd, "OPENIO", object, (void**)&bo);
        if (!flag) g_print("Error on creating :(\n");
    }
}

void iterator_test() {
    struct oio_error_s* err = NULL;
    JBackendData* bd = NULL;

    backend_init("new_container", (void**)&bd);
    fill_container(bd);

    JBackendIterator* bi = NULL;

    gboolean flag = backend_get_all(bd, "OPENIO", (void**)&bi);

    char* name = NULL;
   
    g_print("List of all objects: ");
    while (backend_iterate(bd, bi, &name)) {
        g_print("%s, ", name);        
    } 
    g_print("NULL\n");

    iterator_free(bi);

    bi = NULL;

    flag = backend_get_by_prefix(bd, "OPENIO", "foo", (void**)&bi);

    g_print("List of objects with prefix `foo`: ");
    while (backend_iterate(bd, bi, &name)) {
        g_print("%s, ", name);
    }
    g_print("NULL\n");

    iterator_free(bi);

    bi = NULL;

    flag = backend_get_by_prefix(bd, "OPENIO", "obj", (void**)&bi);

    g_print("List of objects with prefix `obj`: ");
    while (backend_iterate(bd, bi, &name)) {
        g_print("%s, ", name);
    }
    g_print("NULL\n");

}

int main()  {
    short_test();
    iterator_test();
}
