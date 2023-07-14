### [JBackend](https://julea-io.github.io/julea/structJBackend.html)
Is a union of `object`, `kv` and `db`. Each of these structures has only pointers to functions in its fields. \
Set of functions in `object` structure: 
* [`backend_init`](https://julea-io.github.io/julea/structJBackend.html#a98b24d2dec1d3809e960d4bf058d4c58) initializes `JBackendData structure` (`oio_sds_init` probably) - just setups all necessary things for starting work \
   `gboolean backend_init(gchar const*, gpointer* )`
* [`backend_fini`](https://julea-io.github.io/julea/structJBackend.html#a2116424a6ea324d340e5d0e37855853f) frees the structure and unmounts OPenIO (`oio_sds_free` probably) \
   `void backend_fini(gpointer)`
* [`backend_create`](https://julea-io.github.io/julea/structJBackend.html#a288b932e7d259e96b88986ed68aad1fc) creates a new object in desired container? what do arguments mean?
   `gboolean backend_create(gpointer data, gchar const* namespace, gchar const* path, gpointer* data)`
* [`backend_open`](https://julea-io.github.io/julea/structJBackend.html#a352b421d2137bfd54b3579d4faca9056) - probably smth like opening a file, but I don't see the analogue of an object storage \
  `gboolean backend_open(gpointer object_backend, gchar const* namespace, gchar const* name, gpointer* object_handle)`
* [`backend_delete`](https://julea-io.github.io/julea/structJBackend.html#a8ea6a1478a2a65ee9a902c64515348d1) deletes an object or a container? \
  `gboolean backend_delete(gpointer object_backend, gpointer object_handle)`
* [`backend_close`](https://julea-io.github.io/julea/structJBackend.html#aa1f31e0e04d44cff7475f6e3c904b79b) closes a file? like closes an object? \
  `gboolean backend_close(gpointer object_backend, gpointer object_handle)`
* [`backend_status`](https://julea-io.github.io/julea/structJBackend.html#a70d6e5529678d206bee4bae2799dd7b9) stat analogue. Should it show the description just like `openio container show my_container` or output metadata? \
  `gboolean backend_status(gpointer object_backend, gpointer object_handle, gint64* modification_time,  guint64* size)`
* [`backend_sync`](https://julea-io.github.io/julea/structJBackend.html#ab90502d987237c20a351dbffe6750e56) - syncs with the block device ???? \
  `gboolean backend_sync(gpointer object_backend, gpointer object_handle)`
* [`backend_read`](https://julea-io.github.io/julea/structJBackend.html#ac03a157dbaaa8cb99e55d0a62e3205cc) reads from a file \
  `gboolean backend_read(gpointer object_backend, gpointer object_handle, gpointer daata, guint64 length, guint64 offset, guint64* nbytes)`
* [`backend_write`](https://julea-io.github.io/julea/structJBackend.html#a0cbdf4da841989706966161885debb24) writes to an object? affects content probably? \
  `gboolean backend_write(gpointer object_backend, gpointer object_handle, gconstpointer data, guint64 length, guint64 offset, guint64* nbytes)`
* [`backend_get_all`](https://julea-io.github.io/julea/structJBackend.html#a69f4c2d64f1504e9699e1d36e16e8282) - like `readdir` in posix (`ls` analogue) ???? Should use listing functions from C API probably \
  `gboolean backend_get_all(gpointer, gchar const* , gchar const*, gpointer*)`
* [`backend_get_by_prefix`](https://julea-io.github.io/julea/structJBackend.html#a8403b3aee5e71d0e292af8373eb1c0b6) - like `ls` filtering on prefix ????? (there are corresponding listing functions) \
  `gboolean backend_get_by_prefix(gpointer, gchar const*, gchar const*, gpointer* )`
* [`backend_iterate`](https://julea-io.github.io/julea/structJBackend.html#a0b6e7c8e5d5fc89cf4594decba9fffd6) - obtains metadata - takes two iterators as input and fills bson_t* with metadata ??? \
  `gboolean backend_iterate(gpointer, gpointer, gchar const**)`

 May be compared to [BlueStore project](https://github.com/Bella42/julea/blob/objectstore/bluestore/julea_bluestore.h) \
**TODO:**
* check `oio_sds_ul_dst_s` for `write` function. Need to get how to use append, offset, etc. in order not to make extra operations every time
* understand how to get modification time
* probably the good idea will be to find how these functions may be used
File [`oio_sds.h`](https://github.com/open-io/oio-sds/blob/master/core/oio_sds.h) seems to provide better documentation than which is given on the webpage with documentation...
