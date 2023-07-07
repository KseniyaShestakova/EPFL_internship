#include "oio_sds.h"
//#include "oio_core.h"

int main() {
	struct oio_sds_s *client = NULL;
	struct oio_error_s *err = NULL;
	err = oio_sds_init(&client, 0);
	g_assert_no_error((GError*)err);
}
