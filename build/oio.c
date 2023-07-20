#include "oio_sds.h"
#include "oio_core.h"

#include <julea-config.h>

#include <glib.h>
#include <gmodule.h>

#include <julea.h>


static gboolean
backend_create(gpointer backend_data, gchar const* namespace, gchar const* path, gpointer* backend_object)
{
	(void)backend_data;
	(void)namespace;
	(void)backend_object;
	(void)path;

	return TRUE;
}

static gboolean
backend_open(gpointer backend_data, gchar const* namespace, gchar const* path, gpointer* backend_object)
{
	(void)backend_data;
	(void)namespace;
	(void)path;
	(void)backend_object;

	return TRUE;
}

static gboolean
backend_delete(gpointer backend_data, gpointer backend_object)
{
	(void)backend_data;
	(void)backend_object;

	return TRUE;
}

static gboolean
backend_close(gpointer backend_data, gpointer backend_object)
{
	(void)backend_data;	
	(void)backend_object;

	return TRUE;
}

static gboolean
backend_status(gpointer backend_data, gpointer backend_object, gint64* modification_time, guint64* size)
{
	(void)backend_data;
	(void)backend_object;
	(void)modification_time;
	(void)size;

    *modification_time = 2;
    *size = 2;
	
	return TRUE;
}

static gboolean
backend_sync(gpointer backend_data, gpointer backend_object)
{
	(void)backend_data;
	(void)backend_object;

	return TRUE;
}

static gboolean
backend_read(gpointer backend_data, gpointer backend_object, gpointer buffer, guint64 length, guint64 offset, guint64* bytes_read)
{
	(void)backend_data;
	(void)backend_object;
	(void)buffer;
	(void)length;
	(void)offset;
	(void)bytes_read;

    *bytes_read = 2;

	return TRUE;
}

static gboolean
backend_write(gpointer backend_data, gpointer backend_object, gconstpointer buffer, guint64 length, guint64 offset, guint64* bytes_written)
{
	(void)backend_data;
	(void)backend_object;
	(void)buffer;
	(void)length;
	(void)offset;
	(void)bytes_written;

    *bytes_written = 2;

	return TRUE;
}

static gboolean
backend_get_all(gpointer backend_data, gchar const* namespace, gpointer* backend_iterator)
{
	(void)backend_data;
	(void)namespace;
	(void)backend_iterator;

	return TRUE;
}

static gboolean
backend_get_by_prefix(gpointer backend_data, gchar const* namespace, gchar const* prefix, gpointer* backend_iterator)
{
	(void)backend_data;
	(void)namespace;
	(void)prefix;
	(void)backend_iterator;

	return TRUE;
}

static gboolean
backend_iterate(gpointer backend_data, gpointer backend_iterator, gchar const** name)
{
	(void)backend_data;
	(void)backend_iterator;
	(void)name;

	return FALSE;
}

static gboolean
backend_init(gchar const* path, gpointer* backend_data)
{
	(void)path;
	(void)backend_data;
	
	return TRUE;
}

static void
backend_fini(gpointer backend_data)
{
	(void)backend_data;
}


static JBackend oio_backend = {
	.type = J_BACKEND_TYPE_OBJECT,
	.component = J_BACKEND_COMPONENT_CLIENT | J_BACKEND_COMPONENT_SERVER,
	.object = {
		.backend_init = backend_init,
		.backend_fini = backend_fini,
		.backend_create = backend_create,
		.backend_delete = backend_delete,
		.backend_open = backend_open,
		.backend_close = backend_close,
		.backend_status = backend_status,
		.backend_sync = backend_sync,
		.backend_read = backend_read,
		.backend_write = backend_write,
		.backend_get_all = backend_get_all,
		.backend_get_by_prefix = backend_get_by_prefix,
		.backend_iterate = backend_iterate }
};

G_MODULE_EXPORT
JBackend*
backend_info(void)
{
	return &oio_backend;
}


