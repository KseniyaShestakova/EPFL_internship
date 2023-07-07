/*
Copyright (C) 2017-2019 OpenIO SAS, as part of OpenIO SDS

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3.0 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.
*/

#ifndef OIO__OIO_SDS_CORE_CLIENT_VARIABLES_H_
#define OIO__OIO_SDS_CORE_CLIENT_VARIABLES_H_

#include "core/oiovar.h"

/* AUTO-GENERATED by confgen.py */

#ifndef OIO_CORE_CHUNK_SIZE_MAX
# define OIO_CORE_CHUNK_SIZE_MAX (0)
#endif

extern gint64 oio_chunk_size_maximum;

#ifndef OIO_CORE_CHUNK_SIZE_MIN
# define OIO_CORE_CHUNK_SIZE_MIN (10000000)
#endif

extern gint64 oio_chunk_size_minimum;

#ifndef OIO_CORE_HTTP_USER_AGENT
# define OIO_CORE_HTTP_USER_AGENT ""
#endif

extern gchar oio_core_http_user_agent[64];

#ifndef OIO_CORE_PERIOD_REFRESH_CPU_IDLE
# define OIO_CORE_PERIOD_REFRESH_CPU_IDLE (1 * G_TIME_SPAN_SECOND)
#endif

extern gint64 _refresh_cpu_idle;

#ifndef OIO_CORE_PERIOD_REFRESH_IO_IDLE
# define OIO_CORE_PERIOD_REFRESH_IO_IDLE (1 * G_TIME_SPAN_SECOND)
#endif

extern gint64 _refresh_io_idle;

#ifndef OIO_CORE_PERIOD_REFRESH_MAJOR_MINOR
# define OIO_CORE_PERIOD_REFRESH_MAJOR_MINOR (30 * G_TIME_SPAN_SECOND)
#endif

extern gint64 _refresh_major_minor;

#ifndef OIO_CORE_SDS_ADAPT_METACHUNK_SIZE
# define OIO_CORE_SDS_ADAPT_METACHUNK_SIZE (TRUE)
#endif

extern gboolean oio_sds_client_patch_metachunk_size;

#ifndef OIO_CORE_SDS_AUTOCREATE
# define OIO_CORE_SDS_AUTOCREATE (FALSE)
#endif


#ifndef OIO_CORE_SDS_NOSHUFFLE
# define OIO_CORE_SDS_NOSHUFFLE (FALSE)
#endif

extern gboolean oio_sds_no_shuffle;

#ifndef OIO_CORE_SDS_STRICT_UTF8
# define OIO_CORE_SDS_STRICT_UTF8 (TRUE)
#endif

extern gboolean oio_url_must_be_unicode;

#ifndef OIO_CORE_SDS_TIMEOUT_CNX_RAWX
# define OIO_CORE_SDS_TIMEOUT_CNX_RAWX (5.0)
#endif

extern gdouble oio_client_rawx_timeout_cnx;

#ifndef OIO_CORE_SDS_TIMEOUT_REQ_RAWX
# define OIO_CORE_SDS_TIMEOUT_REQ_RAWX (60.0)
#endif

extern gdouble oio_client_rawx_timeout_req;

#ifndef OIO_CORE_SDS_VERSION
# define OIO_CORE_SDS_VERSION "4.2"
#endif

extern gchar oio_sds_client_version[64];

#ifndef OIO_META2_MAX_VERSIONS
# define OIO_META2_MAX_VERSIONS (1)
#endif

extern gint64 meta2_max_versions;

#ifndef OIO_SOCKET_PROXY_BUFLEN
# define OIO_SOCKET_PROXY_BUFLEN (0)
#endif

extern guint oio_socket_proxy_buflen;

#ifndef OIO_SOCKET_RAWX_BUFLEN
# define OIO_SOCKET_RAWX_BUFLEN (0)
#endif

extern guint oio_socket_rawx_buflen;

#ifndef OIO_SQLX_OUTGOING_TIMEOUT_REQ
# define OIO_SQLX_OUTGOING_TIMEOUT_REQ (30.0)
#endif

extern gdouble oio_sqlx_timeout_req;


#endif /* OIO__OIO_SDS_CORE_CLIENT_VARIABLES_H_ */
