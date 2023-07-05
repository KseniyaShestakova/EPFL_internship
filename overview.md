### [JBackend](https://julea-io.github.io/julea/structJBackend.html)
Is a union of `object`, `kv` and `db`. Each of these structures has only pointers to functions in its fields. \
Set of functions in `object` structure: 
* `backend_init` initializes `JBackendData structure` and fills the path variable with path, inits OpenIO, 
* `backend_fini`unmounts OpenIO and frees the structure, 
* `backend_create` creats a file
* `backend_open` opens a file
* `backend_delete` deletes a file
* `backend_close` closes a file
* `backend_status` stat analogue
* `backend_sync` - syncs with the block device ????
* `backend_read` reads from a file
* `backend_write` writes to a file
* `backend_get_all` - like `readdir` in posix (`ls` analogue) ????
* `backend_get_by_prefix` - like `ls` filtering on prefix ?????
* `backend_iterate` - obtains metadata - takes two iterators as input and fills bson_t* with metadata ???


I didn't find clear explanations of their semantics, 
thus I can only guess that they should do something similar to standard filesystems
 (like those implemented with futex). \
 May be compared to [BlueStore project](https://github.com/Bella42/julea/blob/objectstore/bluestore/julea_bluestore.h) \
