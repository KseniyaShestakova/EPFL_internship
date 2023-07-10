#include "oio_sds.h"
#include "oio_core.h"

#include <stdio.h>

static const char* ns = "OPENIO";
static const char* account = "ACCOUNT";
static const char* user = "CONTAINER";

int main() {
	struct oio_sds_s *client = NULL;
	struct oio_error_s *err = NULL;
	err = oio_sds_init(&client, ns);
	g_assert_no_error((GError*)err);
	printf("Created oio_sds_s with namespace: %s...\n", ns);

	// creating a container
	struct oio_url_s* url = oio_url_empty();
	g_assert_nonnull(url);
	printf("Created empty url...\n");

	oio_url_set(url, OIOURL_NS, ns);
	oio_url_set(url, OIOURL_ACCOUNT, account);
	oio_url_set(url, OIOURL_USER, user);

	err = oio_sds_create(client, url);
	oio_url_clean(url);
	g_assert_no_error((GError*)err);
	printf("Created and cleaned url with parametres: %s, %s, %s\n", ns, account, user);

}
