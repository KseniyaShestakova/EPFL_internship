/*
Copyright (C) 2017-2019 OpenIO SAS, as part of OpenIO SDS

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OIO__OIO_SDS_RESOLVER_RESOLVER_VARIABLES_H_
#define OIO__OIO_SDS_RESOLVER_RESOLVER_VARIABLES_H_

#include "core/oiovar.h"

/* AUTO-GENERATED by confgen.py */

#ifndef OIO_CORE_RESOLVER_DIR_SHUFFLE
# define OIO_CORE_RESOLVER_DIR_SHUFFLE (TRUE)
#endif

extern gboolean oio_resolver_dir_shuffle;

#ifndef OIO_CORE_RESOLVER_SRV_SHUFFLE
# define OIO_CORE_RESOLVER_SRV_SHUFFLE (TRUE)
#endif

extern gboolean oio_resolver_srv_shuffle;

#ifndef OIO_RESOLVER_CACHE_CSM0_MAX_DEFAULT
# define OIO_RESOLVER_CACHE_CSM0_MAX_DEFAULT (4194304)
#endif

extern guint oio_resolver_m0cs_default_max;

#ifndef OIO_RESOLVER_CACHE_CSM0_TTL_DEFAULT
# define OIO_RESOLVER_CACHE_CSM0_TTL_DEFAULT (0)
#endif

extern gint64 oio_resolver_m0cs_default_ttl;

#ifndef OIO_RESOLVER_CACHE_ENABLED
# define OIO_RESOLVER_CACHE_ENABLED (FALSE)
#endif

extern gboolean oio_resolver_cache_enabled;

#ifndef OIO_RESOLVER_CACHE_SRV_MAX_DEFAULT
# define OIO_RESOLVER_CACHE_SRV_MAX_DEFAULT (4194304)
#endif

extern guint oio_resolver_srv_default_max;

#ifndef OIO_RESOLVER_CACHE_SRV_TTL_DEFAULT
# define OIO_RESOLVER_CACHE_SRV_TTL_DEFAULT (0)
#endif

extern gint64 oio_resolver_srv_default_ttl;


#endif /* OIO__OIO_SDS_RESOLVER_RESOLVER_VARIABLES_H_ */
