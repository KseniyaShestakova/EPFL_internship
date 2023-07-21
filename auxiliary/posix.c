// this part is for better understanding of
// how hash tables are used in posix implementation
#include <julea-config.h>

#include <glib.h>
#include <glib/gstdio.h>
#include <gmodule.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <julea.h>

struct JBackendData
{
	gchar* path;
	/// \todo check whether hash tables can stay global
};

typedef struct JBackendData JBackendData;

struct JBackendIterator
{
	JDirIterator* iterator;
	gchar* prefix;
};

typedef struct JBackendIterator JBackendIterator;

struct JBackendObject
{
	gchar* path;
	gint fd;
	guint ref_count;
};

typedef struct JBackendObject JBackendObject;

static guint jd_num_backends = 0;

static GHashTable* jd_backend_file_cache = NULL;

G_LOCK_DEFINE_STATIC(jd_backend_file_cache);

static void
jd_backend_files_free(gpointer data) {
    GHashTable* files = data;

    g_hash_table_destroy(files);
}

// thread local variable
// macro accepts a function for deallocating memory when thread exits
static GPrivate jd_backend_files = G_PRIVATE_INIT(jd_backend_files_free);

static void
backend_file_unref(gpointer data) {
    JBackendObject* bo = data;

    g_return_if_fail(bo != NULL);

    G_LOCK(jd_backend_file_cache);

    // if we are removing the last reference
    if (g_atomic_int_dec_and_test(&(bo->ref_count))) {
        // remove from hash table
        g_hash_table_remove(jd_backend_file_cache, bo->path);

        /*do some work to close a file */

        g_free(bo->path);
        g_slice_free(JBackendObject, bo);
    }

    G_UNLOCK(jd_backend_file_cache);
}

// get value of a thread local variable
static GHashTable*
jd_backend_files_get_thread(void)
{
    GHashTable* files;
    files = g_private_get(&jd_backend_files);

    // if we got NULL
    if (G_UNLIKELY(files == NULL)) {
        files = g_hash_table_new_full(/*hash_func*/g_str_hash,
                                      /*equal_func*/g_str_equal,
                                      /*key_destroy_func*/NULL,
                                      /*value_destroy_func*/backend_file_unref);
        g_private_replace(&jd_backend_files, files);
    }

    return files;
}

// getting object from hash table
// if already present in hash table, then it is returned
// else a new kv-pair is inserted into hash table and returned
// object should exist in global hash table
static JBackendObject*
backend_file_get(GHashTable* files, gchar const* key) {
    JBackendObject* bo;

    if ((bo = g_hash_table_lookup(files, key)) != NULL) {
        return bo;
    } 

    // lock global cache before accessing it
    G_LOCK(jd_backend_file_cache);

    if ((bo = g_hash_table_lookup(jd_backend_file_cache, key)) != NULL) {
        // increment ref_count
        g_atomic_int_inc(&(bo->ref_count));
        // insert into files
        g_hash_table_insert(files, bo->path, bo);
        G_UNLOCK(jd_backend_file_cache);
    }

    // Not unlocked if NULL is returned!
    // The caller is supposed to call backend_file_add() if NULL is returned

    return bo;
}

// adding a new file
static void
backend_file_add(GHashTable* files, JBackendObject* object) {
    if (object != NULL) {
        g_hash_table_insert(jd_backend_file_cache, object->path, object);
        g_hash_table_insert(files, object->path, object);
    }

    G_UNLOCK(jd_backend_file_cache);
}

// further you will see only a brief description of 
// how hash table is used in different functions
// seems like it does not actually return TRUE if and only if 
// file didn't exist and was successfully created
static gboolean(gpointer backend_data, gchar const* namespace,
                gchar const* path, gpointer* backend_object) {
    JBackendData* bd = backend_data;
    // get only thread-local version of the hash table
    GHashTable* files = jd_backend_files_get_thread();
    JBackendObject* bo = NULL;

    /* some other preparation */

    // if such path is already present in hash-table
    if ((bo = backend_file_get(files, full_path)) != NULL) {
        g_free(full_path);
        fd = bo->fd; // todo stays here

        goto end;

    }

    /* some more preparation */

    fd = open(full_path, O_RDWR | O_CREAT, 0600);

    // if we cannot open this file
    if (fd == -1) {
        backend_file_add(files, NULL);
        goto end;
    }

    /* form new valid file in bo */

    backend_file_add(files, bo);

end:

    *backend_object = bo;

    return (fd != -1);
}


static gboolean
backend_open(gpointer backend_data, gchar const* namespace,
             gchar const* path, gpointer* backend_object) {
    /* the difference from create method:
     * in create the file is opened with O_RDWR | O_CREAT flag
     * and parent directory was created in case it didn't exist previously
     * here the file is opened with O_RDWR flag
     * everything else is just the same
     *
     */
}

static gboolean
backend_delete(gpointer backend_data, gpointer backend_object) {
    JBackendObkect* bo = backend_object;
    GHashTable* files = jd_backend_files_get_thread();
    gboolean ret;

    (void)backend_data;

    j_trace_file_begin(bo->path, J_TRACE_FILE_DELETE);
    // wrapper over POSIX unlink()
    // deletes filename from the file_system
    // if it was the last link, memory under this file will be freed
    ret = (g_unlink(bo->path) == 0);
    j_trace_file_end(bo->path, J_TRACE_FILE_DELETE, 0, 0);

    // deletes from thread-local cache
    // but still can be present in the global one
    g_hash_table_remove(files, bo->path);

    return ret;
}

// just removes from hash table
static gboolean
backend_close(gpointer backend_data, gpointer backend_object)
{
	JBackendObject* bo = backend_object;
	GHashTable* files = jd_backend_files_get_thread();
	gboolean ret;

	(void)backend_data;

	ret = g_hash_table_remove(files, bo->path);

	return ret;
}

static gboolean
backend_status(gpointer backend_data, gpointer backend_object,
               gint64* modification_time, gint64* size) {
    /* does not deal with hash table
     * probably existence is checked in preceeding open call or like that
     * */
}

static gboolean
backend_sync(gpointer backend_data, gpointer backend_object) {
    /* does mnot deal with hash table
     * just calls POSIX function fsync
     * */
}

static gboolean
backend_read(gpointer backend_data, gpointer backend_object,
                gpointer buffer,
                guint64 length, guint64 offset,
                guint64* bytes_read) {
    /* does not deal with hash-table
     * seems like before each read
     * there is an open call (in a wrapper)
     * */
}

static gboolean
backend_write(gpointer backend_data, gpointer backend_object,
              gconstpointer buffer,
              guint64 length, guint64 offset,
              giunt64* bytes_written) {
    /* also does not touch hash-table
     * because of preceeding open call, probale
     * */
}

/* get_all,
 * get_by_prefix,
 * iterate
 * also don't touch hash-table
 * because they are only working with iterators
 */

static gboolean
backend_init(gchar const* path, gpointer* backend_data)
{
	JBackendData* bd;

	bd = g_slice_new(JBackendData);
	bd->path = g_strdup(path);

	jd_backend_file_cache = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);

	g_mkdir_with_parents(path, 0700);

	g_atomic_int_inc(&jd_num_backends);

	*backend_data = bd;

	return TRUE;
}

static void
backend_fini(gpointer backend_data)
{
	JBackendData* bd = backend_data;

	if (g_atomic_int_dec_and_test(&jd_num_backends))
	{
		g_assert(g_hash_table_size(jd_backend_file_cache) == 0);
		g_hash_table_destroy(jd_backend_file_cache);
	}

	g_free(bd->path);
	g_slice_free(JBackendData, bd);
}









