#include "oio_sds.h"
#include "oio_core.h"

#include <stdio.h>
#include <string.h>

static const char* ns = "OPENIO";
static const char* account = "ACCOUNT";
static const char* user = "CONTAINER";


void print_element(void* ctx, const char* key, const char* value) {
	(void) ctx;
	g_print("\"%s\" : \"%s\", ", key, value);
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
    return url;
}


void container_example(struct oio_sds_s* client) {
    struct oio_url_s* url = create_empty_url();

    basic_init(url, NULL);

    struct oio_error_s* err_on_creating = oio_sds_create(client, url);
    oio_url_clean(url);

    g_assert_no_error((GError*)err_on_creating);
    g_print("Successfully created a container.\n\n");
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
    oio_url_clean(url);

    g_assert_no_error((GError*)err_on_uploading);
    g_print("Data was successfully uploaded...\n");
    g_assert_no_error((GError*)err_on_downloading);
    g_print("Data was successfully downloaded...\n");

    g_print("Resulting buffer contains: %s\n", data);
    g_print("Passed object example.\n\n");

    fflush(stdout);
}

void metadata_example(struct oio_sds_s* client, struct oio_error_s* err) {
    struct oio_url_s* container_url = create_empty_url();
    struct oio_url_s* object_url = create_empty_url();

    basic_init(container_url, NULL);
    basic_init(object_url, "object.txt");

    const gchar* const container_properties[5] = { "color", "red", "flag", "true", NULL};
    const gchar* const object_properties[5] = {"color", "blue", "flag", "false", NULL};

    err = 
        oio_sds_set_container_properties(client, container_url, container_properties);
    g_assert_no_error((GError*)err);
    err = oio_sds_set_content_properties(client, object_url, object_properties);
    g_assert_no_error((GError*)err);

    g_print("Container metadata: {");
    err = oio_sds_get_container_properties(client, container_url, print_element, NULL);
    oio_url_clean(container_url);
    g_assert_no_error((GError*)err);
    g_print("}\n");

    g_print("Object metadata: {");
    err = oio_sds_get_content_properties(client, object_url, print_element, NULL);
    oio_url_clean(object_url);
    g_assert_no_error((GError*)err);
    g_print("}\n");

    g_print("Passed metadata example.\n\n");

    fflush(stdout);
}

void fill_container(struct oio_sds_s* client, struct oio_error_s* err) {
    struct oio_url_s* url = create_empty_url();
    basic_init(url, NULL);

    err = oio_sds_create(client, url); // creating a container
    g_assert_no_error((GError*)err);

    struct oio_sds_ul_dst_s dst = OIO_SDS_UPLOAD_DST_INIT;
    dst.url = url;
    gchar data[] = "Sample";
    gchar foo[] = "foo/_";
    size_t foo_pos = strlen(foo) - 1;
    gchar object[] = "obj_";
    size_t object_pos = strlen(object) - 1;

    for (char i = 'a'; i < 'e'; ++i) {
        foo[foo_pos] = i;
        oio_url_set(url, OIOURL_PATH, foo);
        err = oio_sds_upload_from_buffer(client, &dst, data, sizeof(data));
        g_assert_no_error((GError*)err);
    }

    for (char i = '0'; i < '5'; ++i) {
        object[object_pos] = i;
        oio_url_set(url, OIOURL_PATH, object);
        err = oio_sds_upload_from_buffer(client, &dst, data, sizeof(data));
        g_assert_no_error((GError*)err);
    }

    oio_url_clean(url);
}

// simply outputs the list of all objects in a container
void basic_listing(struct oio_sds_s* client, struct oio_error_s* err) {
    struct oio_url_s* url = create_empty_url();
    basic_init(url, NULL);

    struct oio_sds_list_param_s list_in = {
        .url = url,
        .prefix = NULL, .marker = NULL, .end = NULL, .delimiter = 0, .max_items = 0,
        .flag_allversions = 1, .flag_nodeleted = 1, .flag_properties = 1
    };

    int _print_item(void* ctx, const struct oio_sds_list_item_s* item) {
        (void) ctx;
        g_print("%s, ", item->name);
        return 0;
    }

    struct oio_sds_list_listener_s list_out = {
        .ctx = NULL,
        .on_item = _print_item, .on_prefix = NULL, .on_bound = NULL
    };

    g_print("List of all items: ");
    err = oio_sds_list(client, &list_in, &list_out);
    oio_url_clean(url);
    g_assert_no_error((GError*)err);
    
    g_print("END\n");
    fflush(stdout);
}

// uses markers for outputing the list of all items in portions
void marker_listing(struct oio_sds_s* client, struct oio_error_s* err) {
    g_print("Example of listing with markers and max_item restriction was started...\n");
    
    struct oio_url_s* url = create_empty_url();
    basic_init(url, NULL);

    struct oio_sds_list_param_s list_in = {
        .url = url,
        .prefix = NULL, .marker = NULL, .end = NULL, .delimiter = 0, .max_items = 4,
        .flag_allversions = 1, .flag_nodeleted = 1, .flag_properties = 1
    };

    gboolean save_marker;
    gchar marker[16];
    int _print_item(void* ctx, const struct oio_sds_list_item_s* item) {
        (void) ctx;
        g_print("%s, ", item->name);
        if (save_marker) {
            g_strlcpy(marker, item->name, 16);
            save_marker = FALSE;
        }
        return 0;
    }

    struct oio_sds_list_listener_s list_out = {
        .ctx = NULL,
        .on_item = _print_item, .on_prefix = NULL, .on_bound = NULL
    };

    marker[0] = '\0';
    do {
        g_print("Objects: [");
        save_marker = TRUE;
        list_in.marker = marker;
        err = oio_sds_list(client, &list_in, &list_out);
        g_assert_no_error((GError*)err);
        g_print("]\n");
    } while (list_out.out_count);

    oio_url_clean(url);
}

// output only objects starting with "foo"
void prefix_listing(struct oio_sds_s* client, struct oio_error_s* err) {
    g_print("Starting prefix example...\n");

    struct oio_url_s* url = create_empty_url();
    basic_init(url, NULL);

    struct oio_sds_list_param_s list_in = {
        .url = url,
        .prefix = "foo", .marker = NULL, .end = NULL, .delimiter = 0, .max_items = 0,
        .flag_allversions = 1, .flag_nodeleted = 1, .flag_properties = 1
    };

    int _print_item(void* ctx, const struct oio_sds_list_item_s* item) {
        (void) ctx;
        g_print("%s, ", item->name);
        return 0;
    }

    struct oio_sds_list_listener_s list_out = {
        .ctx = NULL,
        .on_item = _print_item, .on_prefix = NULL, .on_bound = NULL
    };

    g_print("Objects with desired prefix: ");
    err = oio_sds_list(client, &list_in, &list_out);
    oio_url_clean(url);
    g_assert_no_error((GError*)err);
    g_print("END\n");
}

// excludes all the objects whose names contain delimiter
void delimiter_listing(struct oio_sds_s* client, struct oio_error_s* err) {
    g_print("Starting delimiter example...\n");

    struct oio_url_s* url = create_empty_url();
    basic_init(url, NULL);

    struct oio_sds_list_param_s list_in = {
        .url = url,
        .prefix = NULL, .marker = NULL, .end = NULL, .delimiter = '/', .max_items = 0,
        .flag_allversions = 1, .flag_nodeleted = 1, .flag_properties = 1
    };

    int _print_item(void* ctx, const struct oio_sds_list_item_s* item) {
        (void) ctx;
        g_print("%s, ", item->name);
        return 0;
    }

    struct oio_sds_list_listener_s list_out = {
        .ctx = NULL,
        .on_item = _print_item, .on_prefix = NULL, .on_bound = NULL
    };

    g_print("Objects without delimeter: ");
    err = oio_sds_list(client, &list_in, &list_out);
    oio_url_clean(url);
    g_assert_no_error((GError*)err);
    g_print("END\n");
}

void listing_example(struct oio_sds_s* client, struct oio_error_s* err) {
    fill_container(client, err);

    basic_listing(client, err);

    marker_listing(client, err);

    prefix_listing(client, err);

    delimiter_listing(client, err);

    g_print("Passed listing example.\n\n");
    fflush(stdout);
}

// in this case cleaning up means deleting current container
// only empty container may be deleted
// thus we need to delete objects inside the container first
void clean_up(struct oio_sds_s* client, struct oio_error_s* err) {
    g_print("Started cleaning up...\n");

    struct oio_url_s* url = create_empty_url();
    basic_init(url, NULL);

    struct oio_sds_list_param_s list_in = {
        .url = url,
        .prefix = NULL, .marker = NULL, .end = NULL, .delimiter = 0, .max_items = 0,
        .flag_allversions = 1, .flag_nodeleted = 1, .flag_properties = 1
    };

    int _delete_item(void* ctx, const struct oio_sds_list_item_s* item) {
        (void) ctx;
        g_print("Deleting item: %s...\n", item->name);

        struct oio_url_s* tmp_url = create_empty_url();
        basic_init(tmp_url, item->name);

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

    g_print("Deleting container...");
    url = create_empty_url();
    basic_init(url, NULL);

    err = oio_sds_delete_container(client, url);
    g_assert_no_error((GError*)err);
    oio_url_clean(url);

    g_print("Cleaning up done.\n\n");
    fflush(stdout);
}

void run_all_examples() {
    struct oio_sds_s* client = NULL;
    struct oio_error_s* err = NULL;
    err = oio_sds_init(&client, ns);
    g_assert_no_error((GError*)err);
    g_print("Created oio_sds_s in namespace: %s...\n", ns);
    g_print("Starting examples...\n\n");

    container_example(client);

    object_example(client);

    metadata_example(client, err);

    listing_example(client, err);

    clean_up(client, err);
}


int main() {
    run_all_examples();
}
