#include "oio_sds.h"
#include "oio_core.h"

#include <stdio.h>
#include <string.h>

static const char* _ns_ = "OPENIO";
static const char* _account_ = "ACCOUNT";
static const char* _user_ = "CONTAINER";

struct Iterator {
    char* marker;
};

typedef struct Iterator Iterator;

void basic_init(struct oio_url_s* url, const char* name) {
	oio_url_set(url, OIOURL_NS, _ns_);
    oio_url_set(url, OIOURL_ACCOUNT, _account_);
    oio_url_set(url, OIOURL_USER, _user_);
    if (name != NULL) {
        oio_url_set(url, OIOURL_PATH, name);
    }
}

struct oio_url_s* create_empty_url() {
    struct oio_url_s* url = oio_url_empty();
    g_assert_nonnull(url);
    return url;
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

Iterator* new_iterator(struct oio_sds_s* client, struct oio_error_s* err) {
    Iterator* it = g_slice_new(Iterator);

    it->marker = g_strdup("");

    return it;
}

void iterator_next(struct oio_sds_s* client, struct oio_error_s* err,
                   Iterator* it,
                   const char* prefix) {
    struct oio_url_s* url = create_empty_url();
    basic_init(url, NULL); // it suggests we know the container we are working in

    struct oio_sds_list_param_s list_in = {
        .url = url,
        .prefix = prefix, .marker = it->marker, .end = NULL, .delimiter = 0,
        .max_items = 1,
        .flag_allversions = 1, .flag_nodeleted = 1, .flag_properties = 1
    };

    gchar marker[256];

    int _print_item(void* ctx, const struct oio_sds_list_item_s* item) {
        (void)ctx;
        g_strlcpy(marker, item->name, 256);
        // after that marker contains name of current item also!
        return 0;
    }

    struct oio_sds_list_listener_s list_out = {
        .ctx = NULL,
        .on_item = _print_item, .on_prefix = NULL, .on_bound = NULL
    };

    err = oio_sds_list(client, &list_in, &list_out);
    g_assert_no_error((GError*)err);

    g_free(it->marker);
    it->marker = g_strdup(marker);
}

char* iterator_get(Iterator* it) {
    return it->marker;
}

void list_one_by_one(struct oio_sds_s* client, struct oio_error_s* err) {
    struct oio_url_s* url = create_empty_url();
    basic_init(url, NULL);

    struct oio_sds_list_param_s list_in = {
        .url = url,
        .prefix = NULL, .marker = NULL, .end = NULL, .delimiter = 0, .max_items = 1,
        .flag_allversions = 1, .flag_nodeleted = 1, .flag_properties = 1
    };

    gchar marker[16];
    marker[0] = 0;

    int _print_item(void* ctx, const struct oio_sds_list_item_s* item) {
        (void) ctx;
        g_print("Current marker: %s, current item: %s\n", marker, item->name);
        g_strlcpy(marker, item->name, 16);
        return 0;
    }

    struct oio_sds_list_listener_s list_out = {
        .ctx = NULL,
        .on_item = _print_item, .on_prefix = NULL, .on_bound = NULL
    };

    do {
        g_print("New iteration...\n");
        list_in.marker = marker;
        err = oio_sds_list(client, &list_in, &list_out);
        g_assert_no_error((GError*)err);
    } while ( list_out.out_count );

    oio_url_clean(url);
}


int main() {
    struct oio_sds_s* client = NULL;
    struct oio_error_s* err = NULL;
    err = oio_sds_init(&client, _ns_);
    g_assert_no_error((GError*)err);

    fill_container(client, err);
    //list_one_by_one(client, err);

    Iterator* it = new_iterator(client, err);

    for (int i = 0; i < 4; ++i) {
        iterator_next(client, err, it, "obj");
        g_print("Step %d: %s\n", i + 1, iterator_get(it));
    }
}
