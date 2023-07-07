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

#include "proxy_variables.h" /* AUTO-GENERATED by confgen.py */

gint32 proxy_enbug_cs_failure_rate = OIO_ENBUG_PROXY_CS_FAILURE_RATE;
gint32 oio_proxy_request_failure_threshold_alone = OIO_ENBUG_PROXY_REQUEST_FAILURE_ALONE;
gint32 oio_proxy_request_failure_threshold_first = OIO_ENBUG_PROXY_REQUEST_FAILURE_FIRST;
gint32 oio_proxy_request_failure_threshold_last = OIO_ENBUG_PROXY_REQUEST_FAILURE_LAST;
gint32 oio_proxy_request_failure_threshold_middle = OIO_ENBUG_PROXY_REQUEST_FAILURE_MIDDLE;
guint proxy_bulk_max_create_many = OIO_PROXY_BULK_MAX_CREATE_MANY;
guint proxy_bulk_max_delete_many = OIO_PROXY_BULK_MAX_DELETE_MANY;
gboolean flag_cache_enabled = OIO_PROXY_CACHE_ENABLED;
gboolean oio_proxy_dir_shuffle = OIO_PROXY_DIR_SHUFFLE;
gboolean flag_force_master = OIO_PROXY_FORCE_MASTER;
gchar oio_proxy_location [256] = OIO_PROXY_LOCATION;
gdouble proxy_timeout_common = OIO_PROXY_OUTGOING_TIMEOUT_COMMON;
gdouble proxy_timeout_config = OIO_PROXY_OUTGOING_TIMEOUT_CONFIG;
gdouble proxy_timeout_conscience = OIO_PROXY_OUTGOING_TIMEOUT_CONSCIENCE;
gdouble proxy_timeout_info = OIO_PROXY_OUTGOING_TIMEOUT_INFO;
gdouble proxy_timeout_stat = OIO_PROXY_OUTGOING_TIMEOUT_STAT;
gint64 lb_downstream_delay = OIO_PROXY_PERIOD_CS_DOWNSTREAM;
gint64 lb_upstream_delay = OIO_PROXY_PERIOD_CS_UPSTREAM;
gint64 csurl_refresh_delay = OIO_PROXY_PERIOD_REFRESH_CSURL;
gint64 srvtypes_refresh_delay = OIO_PROXY_PERIOD_REFRESH_SRVTYPES;
gint64 nsinfo_refresh_delay = OIO_PROXY_PERIOD_RELOAD_NSINFO;
gboolean flag_prefer_master_for_read = OIO_PROXY_PREFER_MASTER_FOR_READ;
gboolean flag_prefer_master_for_write = OIO_PROXY_PREFER_MASTER_FOR_WRITE;
gboolean flag_prefer_slave_for_read = OIO_PROXY_PREFER_SLAVE_FOR_READ;
gboolean flag_local_scores = OIO_PROXY_QUIRK_LOCAL_SCORES;
gint64 proxy_request_max_delay = OIO_PROXY_REQUEST_MAX_DELAY;
gboolean oio_proxy_local_patch = OIO_PROXY_SRV_LOCAL_PATCH;
gint oio_proxy_local_prepare = OIO_PROXY_SRV_LOCAL_PREPARE;
gboolean oio_proxy_srv_shuffle = OIO_PROXY_SRV_SHUFFLE;
gint64 ttl_down_services = OIO_PROXY_TTL_SERVICES_DOWN;
gint64 ttl_known_services = OIO_PROXY_TTL_SERVICES_KNOWN;
gint64 ttl_expire_local_services = OIO_PROXY_TTL_SERVICES_LOCAL;
gint64 ttl_expire_master_services = OIO_PROXY_TTL_SERVICES_MASTER;
guint proxy_url_path_maxlen = OIO_PROXY_URL_PATH_MAXLEN;

static void __attribute__ ((constructor))
_declare_gboolean_OIO__OIO_SDS_PROXY_PROXY_VARIABLES_H_ (void) {

	oio_var_register_gint32(
		&proxy_enbug_cs_failure_rate, OIO_VARKIND_size, "enbug.proxy.cs.failure_rate",
		"Proxy probability to fail with 503 on a /cs route",
		OIO_ENBUG_PROXY_CS_FAILURE_RATE, 0, 100);

	oio_var_register_gint32(
		&oio_proxy_request_failure_threshold_alone, OIO_VARKIND_size, "enbug.proxy.request_failure.alone",
		"Really, do not use this!",
		OIO_ENBUG_PROXY_REQUEST_FAILURE_ALONE, 0, 100);

	oio_var_register_gint32(
		&oio_proxy_request_failure_threshold_first, OIO_VARKIND_size, "enbug.proxy.request_failure.first",
		"Really, do not use this!",
		OIO_ENBUG_PROXY_REQUEST_FAILURE_FIRST, 0, 100);

	oio_var_register_gint32(
		&oio_proxy_request_failure_threshold_last, OIO_VARKIND_size, "enbug.proxy.request_failure.last",
		"Really, do not use this!",
		OIO_ENBUG_PROXY_REQUEST_FAILURE_LAST, 0, 100);

	oio_var_register_gint32(
		&oio_proxy_request_failure_threshold_middle, OIO_VARKIND_size, "enbug.proxy.request_failure.middle",
		"Really, do not use this!",
		OIO_ENBUG_PROXY_REQUEST_FAILURE_MIDDLE, 0, 100);

	oio_var_register_guint(
		&proxy_bulk_max_create_many, OIO_VARKIND_size, "proxy.bulk.max.create_many",
		"In a proxy, sets how many containers can be created at once.",
		OIO_PROXY_BULK_MAX_CREATE_MANY, 0, 10000);

	oio_var_register_guint(
		&proxy_bulk_max_delete_many, OIO_VARKIND_size, "proxy.bulk.max.delete_many",
		"In a proxy, sets how many objects can be deleted at once.",
		OIO_PROXY_BULK_MAX_DELETE_MANY, 0, 10000);

	oio_var_register_gboolean(
		&flag_cache_enabled, "proxy.cache.enabled",
		"In a proxy, sets if any form of caching is allowed. Supersedes the value of resolver.cache.enabled.",
		OIO_PROXY_CACHE_ENABLED);

	oio_var_register_alias("proxy.cache.enabled", "Cache");
	oio_var_register_gboolean(
		&oio_proxy_dir_shuffle, "proxy.dir_shuffle",
		"Should the proxy shuffle the meta1 addresses before contacting them, thus trying to perform a better fanout of the requests.",
		OIO_PROXY_DIR_SHUFFLE);

	oio_var_register_gboolean(
		&flag_force_master, "proxy.force.master",
		"In a proxy, should the process ask the target service (with the help of an option in each RPC) to accept the RPC only if it is MASTER on that DB.",
		OIO_PROXY_FORCE_MASTER);

	oio_var_register_alias("proxy.force.master", "ForceMaster");
	oio_var_register_string(
		oio_proxy_location, "proxy.location",
		"Specify the OpenIO SDS location of the service.",
		OIO_PROXY_LOCATION, 256);

	oio_var_register_gdouble(
		&proxy_timeout_common, OIO_VARKIND_time, "proxy.outgoing.timeout.common",
		"In a proxy, sets the global timeout for all the other RPC issued (not conscience, not stats-related)",
		OIO_PROXY_OUTGOING_TIMEOUT_COMMON, 0.1, 60.0);

	oio_var_register_gdouble(
		&proxy_timeout_config, OIO_VARKIND_time, "proxy.outgoing.timeout.config",
		"In a proxy, sets the global timeout for 'config' requests issued",
		OIO_PROXY_OUTGOING_TIMEOUT_CONFIG, 0.1, 60.0);

	oio_var_register_gdouble(
		&proxy_timeout_conscience, OIO_VARKIND_time, "proxy.outgoing.timeout.conscience",
		"In a proxy, sets the global timeout for the RPC to the central cosnience service.",
		OIO_PROXY_OUTGOING_TIMEOUT_CONSCIENCE, 0.1, 60.0);

	oio_var_register_gdouble(
		&proxy_timeout_info, OIO_VARKIND_time, "proxy.outgoing.timeout.info",
		"In a proxy, sets the global timeout for 'info' requests issued",
		OIO_PROXY_OUTGOING_TIMEOUT_INFO, 0.01, 60.0);

	oio_var_register_gdouble(
		&proxy_timeout_stat, OIO_VARKIND_time, "proxy.outgoing.timeout.stat",
		"In a proxy, sets the global timeout for 'stat' requests issued (mostly forwarded for the event-agent)",
		OIO_PROXY_OUTGOING_TIMEOUT_STAT, 0.1, 60.0);

	oio_var_register_gint64(
		&lb_downstream_delay, OIO_VARKIND_epoch, "proxy.period.cs.downstream",
		"In a proxy, sets the period between the refreshes of the load-balancing state from the central conscience.",
		OIO_PROXY_PERIOD_CS_DOWNSTREAM, 0, 60);

	oio_var_register_gint64(
		&lb_upstream_delay, OIO_VARKIND_epoch, "proxy.period.cs.upstream",
		"In a proxy, sets the period between two sendings of services states to the conscience.",
		OIO_PROXY_PERIOD_CS_UPSTREAM, 1, 60);

	oio_var_register_gint64(
		&csurl_refresh_delay, OIO_VARKIND_epoch, "proxy.period.refresh.csurl",
		"In the proxy, tells the period between the reloadings of the conscience URL, known from the local configuration",
		OIO_PROXY_PERIOD_REFRESH_CSURL, 0, 86400);

	oio_var_register_gint64(
		&srvtypes_refresh_delay, OIO_VARKIND_epoch, "proxy.period.refresh.srvtypes",
		"In the proxy, tells the period between two refreshes of the known service types, from the conscience",
		OIO_PROXY_PERIOD_REFRESH_SRVTYPES, 1, 86400);

	oio_var_register_gint64(
		&nsinfo_refresh_delay, OIO_VARKIND_epoch, "proxy.period.reload.nsinfo",
		"In the proxy, tells the period between two refreshes of the namespace configuration, from the conscience",
		OIO_PROXY_PERIOD_RELOAD_NSINFO, 1, 3600);

	oio_var_register_gboolean(
		&flag_prefer_master_for_read, "proxy.prefer.master_for_read",
		"In a proxy, upon a read request, should the proxy prefer a service known to host a MASTER copy of the DB. Supersedes proxy.prefer.slave_for_read",
		OIO_PROXY_PREFER_MASTER_FOR_READ);

	oio_var_register_alias("proxy.prefer.master_for_read", "PreferMaster");
	oio_var_register_gboolean(
		&flag_prefer_master_for_write, "proxy.prefer.master_for_write",
		"In a proxy, upon a write request, should the proxy prefer services known to host the MASTER copy of the DB ",
		OIO_PROXY_PREFER_MASTER_FOR_WRITE);

	oio_var_register_alias("proxy.prefer.master_for_write", "PreferMasterForWrites");
	oio_var_register_gboolean(
		&flag_prefer_slave_for_read, "proxy.prefer.slave_for_read",
		"In a proxy, upon a read request, should the proxy prefer a service known to host a SLAVE copy of the DB.",
		OIO_PROXY_PREFER_SLAVE_FOR_READ);

	oio_var_register_alias("proxy.prefer.slave_for_read", "PreferSlave");
	oio_var_register_gboolean(
		&flag_local_scores, "proxy.quirk.local_scores",
		"In a proxy, tells if the (ugly-as-hell) quirk that sets the score known from the conscience on the corresponding entries in the cache of services 'known to be local'",
		OIO_PROXY_QUIRK_LOCAL_SCORES);

	oio_var_register_alias("proxy.quirk.local_scores", "LocalScores");
	oio_var_register_gint64(
		&proxy_request_max_delay, OIO_VARKIND_time, "proxy.request.max_delay",
		"How long a request might take to execute, when no specific deadline has been received. Used to compute a deadline transmitted to backend services, when no timeout is present in the request.",
		OIO_PROXY_REQUEST_MAX_DELAY, 1 * G_TIME_SPAN_MILLISECOND, 1 * G_TIME_SPAN_HOUR);

	oio_var_register_gboolean(
		&oio_proxy_local_patch, "proxy.srv_local.patch",
		"Should the proxy patch the services descriptions to let the caller prefer local services.",
		OIO_PROXY_SRV_LOCAL_PATCH);

	oio_var_register_alias("proxy.srv_local.patch", "proxy.srv_local.prefer");
	oio_var_register_gint(
		&oio_proxy_local_prepare, OIO_VARKIND_size, "proxy.srv_local.prepare",
		"Should the proxy allocate services with a local preference. 0 for no, 1 for only one local service and 2 for a maimum of services in spite of the location constraints. The value 2 is a quirk that should be avoided unless upon exceptional conditon wherein you accept the risk.",
		OIO_PROXY_SRV_LOCAL_PREPARE, 0, 2);

	oio_var_register_gboolean(
		&oio_proxy_srv_shuffle, "proxy.srv_shuffle",
		"Should the proxy shuffle the meta2 addresses before the query, to do a better load-balancing of the requests.",
		OIO_PROXY_SRV_SHUFFLE);

	oio_var_register_gint64(
		&ttl_down_services, OIO_VARKIND_time, "proxy.ttl.services.down",
		"In the proxy cache, sets the TTL of a service known to be down",
		OIO_PROXY_TTL_SERVICES_DOWN, 0, 1 * G_TIME_SPAN_DAY);

	oio_var_register_gint64(
		&ttl_known_services, OIO_VARKIND_time, "proxy.ttl.services.known",
		"In a proxy, sets the TTL of each service already encountered",
		OIO_PROXY_TTL_SERVICES_KNOWN, 0, 7 * G_TIME_SPAN_DAY);

	oio_var_register_gint64(
		&ttl_expire_local_services, OIO_VARKIND_time, "proxy.ttl.services.local",
		"In the proxy cache, sets the TTL of a local service",
		OIO_PROXY_TTL_SERVICES_LOCAL, 0, 1 * G_TIME_SPAN_DAY);

	oio_var_register_gint64(
		&ttl_expire_master_services, OIO_VARKIND_time, "proxy.ttl.services.master",
		"In a proxy, sets the TTL on each 'known master' entry. That cache is filled each time a redirection to a MASTER occurs, so that we can immediately direct write operation to the service that owns the MASTER copy.",
		OIO_PROXY_TTL_SERVICES_MASTER, 0, 7 * G_TIME_SPAN_DAY);

	oio_var_register_guint(
		&proxy_url_path_maxlen, OIO_VARKIND_size, "proxy.url.path.maxlen",
		"In a proxy, sets the maximum length for the URL it receives. This options protects stack allocation for that URL.",
		OIO_PROXY_URL_PATH_MAXLEN, 32, 65536);
}
