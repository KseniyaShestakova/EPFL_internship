#include "oio_sds.h"
#include "oio_core.h"

#include "string.h"
#include "stdlib.h"

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
    err = oio_sds_upload_from_buffer(client, &ul_dst, content, sizeof(content));
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

    err = oio_sds_show_content(client, url, NULL,
                              _oio_sds_info_reporter,
                              NULL,
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

    load_content_from_file(client, err, url, "/root/file.txt", 0, 9);
    show_content(client, err, url);
    //show_info(client, err, url);

    // works only if file is not already existing
    //save_content_to_file(client, err, url, "/root/test_.txt");

    show_layout(client, err, url);

    // size should be aligned by metachunk boundary
    err = oio_sds_truncate(client, url, 9);
    g_assert_no_error((GError*)err);
    show_content(client, err, url);

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

    if (oio_url_check(url, _ns_, &field)) {
        g_print("It's normal field!\n");
    } else {
        g_print("It's a faulty field :(\n");
    }

    free(field);
    
    oio_url_clean(url);
    oio_sds_free(client);
}

int main() {
    content_retrieving();

}
