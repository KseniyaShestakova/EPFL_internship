#include "oio_sds.h"
#include "oio_core.h"

#define NAMESPACE 0
#define ACCOUNT 0
#define CONTAINER 0

int main() {
	struct oio_sds_s *client = NULL;
	struct oio_error_s *err = NULL;
	err = oio_sds_init(&client, NAMESPACE);
	g_assert_no_error((GError*)err); 

}
