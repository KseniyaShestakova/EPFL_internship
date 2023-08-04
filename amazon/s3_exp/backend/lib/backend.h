#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

static gboolean
backend_create(gpointer backend_data,
               gchar const* ns,
               gchar const* path,
               gpointer* backend_object);

static gboolean
backend_open(gpointer backend_data,
                gchar const* ns,
                gchar const* path,
                gpointer* backend_object);

static gboolean
backend_delete(gpointer backend_data,
               gpointer backend_object);

static gboolean
backend_close(gpointer backend_data,
              gpointer backend_object);

static gboolean
backend_status(gpointer backend_data,
               gpointer backend_object,
               gint64* modification_time,
               guint64* size);

static gboolean
backend_sync(gpointer backend_data, gpointer backend_object);

static gboolean
backend_read(gpointer backend_data,
              gpointer backend_object,
              gpointer buffer,
              guint64 length,
              guint64 offset,
              guint64* bytes_read);

static gboolean
backend_write(gpointer backend_data,
              gpointer backend_object,
              gconstpointer buffer,
              guint64 length,
              guint64 offset,
              guint64* bytes_written);

static gboolean
backend_get_all(gpointer backend_data,
                gchar const* namespace,
                gpointer* backend_iterator);

static gboolean
backend_get_by_prefix(gpointer backend_data,
                      gchar const* namespace,
                      gchar const* prefix,
                      gpointer* backend_iterator);

static gboolean
backend_iterate(gpointer backend_data,
                gpointer backend_iterator,
                gchar const** name);

static gboolean
backend_init(gchar const* path, gpointer* backend_data);

static void
backend_fini(gpointer backend_data);
                
#ifdef __cplusplus
}
#endif
