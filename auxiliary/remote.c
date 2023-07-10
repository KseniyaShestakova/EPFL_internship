#include "oio_sds.h"
#include "oio_core.h"

#include <stdio.h>

static const char* ns = "OPENIO";
static const char* account = "ACCOUNT";
static const char* user = "CONTAINER";

// TODO: this example uses both stdio.h and glib for I/O

void print_element(void* ctx, const char* key, const char* value) {
	(void) ctx;
	printf("\"%s\" : \"%s\", ", key, value);
}

int print_item(void* ctx, const struct oio_sds_list_item_s* item) {
    (void) ctx;
    g_print("%s\n", item->name);
    return 0;
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


void container_example(struct oio_sds_s* client) {
    struct oio_url_s* url = create_empty_url();

    basic_init(url, NULL);

    struct oio_error_s* err_on_creating = oio_sds_create(client, url);
    //struct oio_error_s* err_on_deleting = oio_sds_delete_container(client, url);
    oio_url_clean(url);

    g_assert_no_error((GError*)err_on_creating);
    //g_assert_no_error((GError*)err_on_deleting);
    printf("Successfully created a container.\n\n");
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

void metadata_example(struct oio_sds_s* client, struct oio_error_s* err) {
    // TODO: add metadata example with objects
    struct oio_url_s* container_url = create_empty_url();

    basic_init(container_url, NULL);

    const gchar* const container_properties[5] = { "color", "red", "flag", "true", NULL};

    err = 
        oio_sds_set_container_properties(client, container_url, container_properties);
    g_assert_no_error((GError*)err);

    printf("Container metadata: {");
    err = oio_sds_get_container_properties(client, container_url, print_element, NULL);
    oio_url_clean(container_url);
    g_assert_no_error((GError*)err);
    printf("}\n");

    printf("Passed metadata example.\n\n");

    fflush(stdout);
}

void listing_example(struct oio_sds_s* client, struct oio_error_s* err) {
    struct oio_url_s* url = create_empty_url();

    basic_init(url, NULL);

    // ------------- fill container ---------------------
    err = oio_sds_create(client, url);
    g_assert_no_error((GError*)err);

    struct oio_sds_ul_dst_s dst = OIO_SDS_UPLOAD_DST_INIT;
    dst.url = url;
    gchar data[] = "sample";

    gchar* name = NULL;
    for (int i = 0; i < 5; ++i) {
        name = g_strdup_printf("object%d", i);
        oio_url_set(url, OIOURL_PATH, name);
        err = oio_sds_upload_from_buffer(client, &dst, data, sizeof(data));
        g_free(name);
        g_assert_no_error((GError*)err);
    }

    for (gchar id = 'a'; id <= 'd'; ++id) {
        name = g_strdup_printf("foo/%c", id);
        oio_url_set(url, OIOURL_PATH, name);
        err = oio_sds_upload_from_buffer(client, &dst, data, sizeof(data));
        g_free(name);
        g_assert_no_error((GError*)err);
    }

    oio_url_clean(url);
    //-------------------------------------
    url = create_empty_url();
 
    basic_init(url, NULL);


    struct oio_sds_list_param_s list_in = {
        .url = url,
        .prefix = NULL, .marker = NULL, .end = NULL, .delimiter = 0, .max_items = 0,
        .flag_allversions = 1, .flag_nodeleted = 1, .flag_properties = 1
    };

    // on_item, on_prefix, on_bound are functions, called at corresponding moments
    struct oio_sds_list_listener_s list_out = {
        .ctx = NULL,
        .on_item = print_item, .on_prefix = NULL, .on_bound = NULL
    };

    printf("List of all objects:\n");
    err = oio_sds_list(client, &list_in, &list_out);
    oio_url_clean(url);

    g_assert_no_error((GError*)err);

    printf("Passed listing example.\n\n");

    fflush(stdout);
}


int main() {
    struct oio_sds_s* client = NULL;
    struct oio_error_s* err = NULL;
    err = oio_sds_init(&client, ns);
    g_assert_no_error((GError*)err);
    printf("Created oio_sds_s in namespace: %s...\n", ns);
    printf("Starting examples...\n\n");

    container_example(client);

    object_example(client);

    metadata_example(client, err);

    listing_example(client, err);
}
