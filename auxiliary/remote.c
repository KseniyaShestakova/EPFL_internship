#include "oio_sds.h"
#include "oio_core.h"

#include <stdio.h>

static const char* ns = "OPENIO";
static const char* account = "ACCOUNT";
static const char* user = "CONTAINER";

void print_element(void* ctx, const char* key, const char* value) {
	(void) ctx;
	g_print("\"%s\" : \"%s\"\n", key, value);
}

void basic_init(struct oio_url_s* url, const char* name) {
	oio_url_set(url, OIOURL_NS, ns);
    oio_url_set(url, OIOURL_ACCOUNT, account);
    oio_url_set(url, OIOURL_USER, user);
    if (name != NULL) {
        oio_url_set(url, OIOURL_PATH, name);
    }
}

struct oio_url_s* create_empty_url() {
    struct oio_url_s* url = oio_url_empty();
    g_assert_nonnull(url);
    printf("Created empty url...\n");
    return url;
}

void container_example(struct oio_sds_s* client, struct oio_error_s* err) {
    struct oio_url_s* url = create_empty_url();

    basic_init(url, NULL);

    err = oio_sds_get_container_properties(client, url, print_element, NULL);
    oio_url_clean(url);
    g_assert_no_error((GError*)err);
    printf("Got container properties.\n\n");
}

void object_example(struct oio_sds_s* client) {
    struct oio_url_s* url = create_empty_url();

    basic_init(url, "object.txt");

    struct oio_sds_ul_dst_s ul_dst = OIO_SDS_UPLOAD_DST_INIT;
    ul_dst.url = url;
    gchar content[] = "Content again";

    // uploaded data from content to ul_dst, pointing to url
    struct oio_error_s* err_on_uploading = 
        oio_sds_upload_from_buffer(client, &ul_dst, content, sizeof(content));

    guchar data[1024];
    // oio_sds_dl_range_s = offset + size
    struct oio_sds_dl_src_s src = { .url = url, .ranges = NULL };
    // may be file, buffer or hook
    struct oio_sds_dl_dst_s dst = { .type = OIO_DL_DST_BUFFER,
        .data = { .buffer = { .ptr = data, .length = sizeof(data) } }
    };

    // downloaded data from src (pointing to url) to dst (with buffer of data)
    struct oio_error_s* err_on_downloading = oio_sds_download(client, &src, &dst); 

    struct oio_error_s* err_on_deleting = oio_sds_delete(client, url);

    oio_url_clean(url);

    g_assert_no_error((GError*)err_on_uploading);
    printf("Data was successfully uploaded...\n");
    g_assert_no_error((GError*)err_on_downloading);
    printf("Data was successfully downloaded...\n");
    g_assert_no_error((GError*)err_on_deleting);
    printf("Object was deleted...\n");

    g_print("Resulting buffer contains: %s\n", data);
    printf("Passed object example.\n\n");

    fflush(stdout);
}


int main() {
	struct oio_sds_s *client = NULL;
	struct oio_error_s *err = NULL;
	err = oio_sds_init(&client, ns);
	g_assert_no_error((GError*)err);
	printf("Created oio_sds_s with namespace: %s...\n", ns);

    container_example(client, err);

    object_example(client);

}
