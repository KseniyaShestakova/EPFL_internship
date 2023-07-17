#include "oio_sds.h"
#include "oio_core.h"

#include "string.h"
#include "stdlib.h"
#include "stdio.h"


static const gchar* _ns_ = "OPENIO";
static const gchar* _account_ = "ACCOUNT";
static const gchar* _user_ = "default_container";

struct oio_url_s* create_empty_url() {
    struct oio_url_s* url = oio_url_empty();
    g_assert_nonnull(url);
    return url;
}

void basic_init(struct oio_url_s* url, const gchar* user, const gchar* path) {
    oio_url_set(url, OIOURL_NS, _ns_);
    oio_url_set(url, OIOURL_ACCOUNT, _account_);

    user = (user != NULL) ? user : _user_;
    oio_url_set(url, OIOURL_USER, user);
    if (path != NULL) {
        oio_url_set(url, OIOURL_PATH, path);
    }
}

void load_content_from_buffer(struct oio_sds_s* client, struct oio_error_s* err,
                  struct oio_url_s* url, gchar* content) {
    struct oio_sds_ul_dst_s ul_dst = OIO_SDS_UPLOAD_DST_INIT;
    ul_dst.url = url;
    g_print("trying to write %ld bytes...\n", strlen(content));
    err = oio_sds_upload_from_buffer(client, &ul_dst, content, strlen(content) + 1);
    g_assert_no_error((GError*)err);
}

void load_content_from_file(struct oio_sds_s* client, struct oio_error_s* err,
                            struct oio_url_s* url, const gchar* file_name,
                            size_t off, size_t len) {
    struct oio_sds_ul_dst_s ul_dst = OIO_SDS_UPLOAD_DST_INIT;
    ul_dst.url = url;
    err = oio_sds_upload_from_file(client, &ul_dst, file_name, off, len);
    g_assert_no_error((GError*)err);
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

void save_content_to_file(struct oio_sds_s* client, struct oio_error_s* err,
                          struct oio_url_s* url, const char* file_name) {
    struct oio_sds_dl_src_s src = { .url = url, .ranges = NULL };
    struct oio_sds_dl_dst_s dst = { .type = OIO_DL_DST_FILE,
                                    .data = { .file = { .path = file_name } }
    };
    err = oio_sds_download(client, &src, &dst);
    g_assert_no_error((GError*)err);
    
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

void show_layout(struct oio_sds_s* client, struct oio_error_s* err,
                 struct oio_url_s* url) {
     void _oio_sds_info_reporter(void* cb_data,
                                enum oio_sds_content_key_e key,
                                const char* value) {
        (void) cb_data;
        switch(key) {
            case OIO_SDS_CONTENT_ID:
                g_print("content_id : ");
                break;
            case OIO_SDS_CONTENT_VERSION:
                g_print("content_version : ");
                break;
            case OIO_SDS_CONTENT_HASH:
                g_print("content_hash : ");
                break;
            case OIO_SDS_CONTENT_SIZE:
                g_print("content_size : ");
                break;
            case OIO_SDS_CONTENT_CHUNKMETHOD:
                g_print("content_chunkmethod : ");
                break;
        }
        g_print("%s\n", value);
    }

    void _oio_sds_property_reporter(void* cb_data,
                                    const char* key,
                                    const char* value) {
        (void) cb_data;
        g_print("meta.%s : %s\n", key, value);
    }

    void _oio_sds_metachunk_reporter(void* cb_data,
                                     unsigned int seq,
                                     size_t offset,
                                     size_t length) {
        (void) cb_data;
        g_print("seq: %d; offset: %ld; length: %ld\n", seq, offset, length);
    }

    err = oio_sds_show_content(client, url, NULL,
                              _oio_sds_info_reporter,
                              _oio_sds_metachunk_reporter,
                              _oio_sds_property_reporter);
    g_assert_no_error((GError*)err);
}


void content_retrieving() {
    struct oio_sds_s* client = NULL;
    struct oio_error_s* err = NULL;
    err = oio_sds_init(&client, _ns_);
    g_assert_no_error((GError*)err);

    // let's create a container
    struct oio_url_s* url = create_empty_url();
    basic_init(url, NULL, NULL);
    err = oio_sds_create(client, url);
    g_assert_no_error((GError*)err);
    oio_url_clean(url);

    // let's create an object inside a container
    url = create_empty_url();
    basic_init(url, NULL, "object.txt");
    gchar content[] = "Content";

    load_content_from_buffer(client, err, url, content);
    show_content(client, err, url);
    //show_info(client, err, url);

    //load_content_from_file(client, err, url, "/root/file.txt", 0, 9);
    //show_content(client, err, url);
    //show_info(client, err, url);

    // works only if file is not already existing
    //save_content_to_file(client, err, url, "/root/test_.txt");

    show_layout(client, err, url);

    // size should be aligned by metachunk boundary
    //err = oio_sds_truncate(client, url, 9);
    //g_assert_no_error((GError*)err);
    //show_content(client, err, url);

    basic_init(url, NULL, "new_object.txt");
    load_content_from_buffer(client, err, url, content);
    show_content(client, err, url);

    // before draining the content let us track usage of the container
    struct oio_sds_usage_s usage;
    err = oio_sds_get_usage(client, url, &usage);
    g_assert_no_error((GError*)err);
    g_print("Used bytes: %ld\n", usage.used_bytes);
    g_print("Quota bytes: %ld\n", usage.quota_bytes);
    g_print("Used objects: %d\n", usage.used_objects);

    oio_url_unset(url, OIOURL_PATH);

    g_print("ID: %s\n", (char*)oio_url_get_id(url));
    g_print("ID size: %ld\n", oio_url_get_id_size(url));

    // after draining the url does not point to a valid content
    // seems like same file can not be drained twice
    //err = oio_sds_drain(client, url);
    //g_assert_no_error((GError*)err);
    
    char* field = malloc(17);
    snprintf(field, 16, "arbitrary_field");

    /*if (oio_url_check(url, _ns_, &field)) {
        g_print("It's normal field!\n");
    } else {
        g_print("It's a faulty field :(\n");
    }*/

    free(field);
    
    oio_url_clean(url);
    oio_sds_free(client);
}

//-----------------------------------------------------------------------------------
// attempts to make a step towards real implementation :)
// creates a new object; is supposed to change *object_handle
// handle type is url!
gboolean _create(gpointer global_handle,
                         gchar const* namespace, gchar const* name,
                         gpointer* object_handle) {

}

gboolean _delete(gpointer global_handle, gpointer object_handle) {

}

gboolean _read(gpointer global_handle, gpointer object_handle,
               gpointer buffer,
               guint64 length, guint64 offset,
               guint64* bytes_read) {

}

gboolean _write(gpointer global_handle, gpointer object_handle,
                gconstpointer data,
                guint64 length, guint64 offset, guint64* bytes_written) {

}

gboolean _status(gpointer global_handle, gpointer object_handle,
                 gint64* modification_time, guint64* size) {

}


//---------------------------------------------------------------
// examples for better understanding of implementation design

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

void get_content_id(struct oio_sds_s* client, struct oio_error_s* err,
                     struct oio_url_s* url, char* content_id) {
    void _oio_sds_info_reporter_id(void* cb_data,
                                   enum oio_sds_content_key_e key,
                                   const char* value) {
        if (key == OIO_SDS_CONTENT_ID) {
            g_print("Current content id: %s\n", value);
            char* id_buffer = (char*)cb_data;
            memcpy(id_buffer, value, strlen(value));
            id_buffer[strlen(value)] = 0;
        }
    }

    err = oio_sds_show_content(client, url, (void*)content_id,
                               _oio_sds_info_reporter_id, NULL, NULL);

    g_assert_no_error((GError*)err);
}


void write_from_buffer(struct oio_sds_s* client, struct oio_error_s* err,
                       struct oio_url_s* url,
                       guint64 length, guint64 offset,
                       gchar* buffer) {
    
    struct oio_sds_ul_dst_s ul_dst = OIO_SDS_UPLOAD_DST_INIT;
    ul_dst.url = url;

    ul_dst.autocreate = 0;
    ul_dst.append = 0;
    ul_dst.partial = 1;

    char content_id[256];
    get_content_id(client, err, url, content_id);
    ul_dst.content_id = content_id;
    g_print("Got content id: %s\n", ul_dst.content_id);

    ul_dst.meta_pos = 0;
    ul_dst.offset = offset;
    ul_dst.chunk_size = 1;

    err = oio_sds_upload_from_buffer(client, &ul_dst, buffer, length);
    g_assert_no_error((GError*)err);
}

void read_to_buffer(struct oio_sds_s* client, struct oio_error_s* err,
                    struct oio_url_s* url,
                    guchar* buffer,
                    guint64 length, guint64 offset,
                    guint64* bytes_read) {
    struct oio_sds_dl_range_s range = { .offset = offset, .size = length };

    struct oio_sds_dl_range_s* ranges_arr[2];
    ranges_arr[0] = &range;
    ranges_arr[1] = NULL;

    struct oio_sds_dl_src_s src = { .url = url,
                                    .ranges = ranges_arr };
    struct oio_sds_dl_dst_s dst = {  .type = OIO_DL_DST_BUFFER,
                                     .data = { .buffer =
                                               { .ptr = buffer, .length = length } }
    };
    err = oio_sds_download(client, &src, &dst);
    g_assert_no_error((GError*)err);

    *bytes_read = dst.out_size;
}



// supposes that container default_container already exists
void read_write_example() {
    struct oio_sds_s* client = NULL;
    struct oio_error_s* err = NULL;
    err = oio_sds_init(&client, _ns_);
    g_assert_no_error((GError*)err);

    struct oio_url_s* url = create_empty_url();
    basic_init(url, NULL,"obj.txt");
    gchar content[] = "Sample content"; // first fill url with this content
    g_print("%ld\n", sizeof(content));

    load_content_from_buffer(client, err, url, content);
    show_content(client, err, url);
    fflush(stdout);

    char buffer[256];
    size_t bytes_read = 0;
    size_t wanted = 4;
    read_to_buffer(client, err, url, buffer, wanted, 1, &bytes_read);
    if (wanted != bytes_read) {
        g_print("Read only %ld bytes):\n", bytes_read);
    } else {
        buffer[bytes_read] = 0;
        g_print("%ld bytes read: %s\n", bytes_read, buffer);    
    }

    guint64 size = 0;
    get_size(client, err, url, &size);
    g_print("Obtained size: %zu\n", size);
    
    show_layout(client, err, url);
    char new_content[] = "hello";
    write_from_buffer(client, err, url, 3, 14, new_content);
    show_content(client, err, url);
}

void quick_init_example() {
    struct oio_sds_s* client = NULL;
    struct oio_error_s* err = NULL;
    err = oio_sds_init(&client, _ns_);
    g_assert_no_error((GError*)err);

    struct oio_url_s* url = oio_url_init("OPENIO/ACCOUNT/container//content_name");
    show_info(client, err, url);
}

int main() {
    content_retrieving();
    quick_init_example();

    read_write_example();

}
