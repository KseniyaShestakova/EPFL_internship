### [JBackend](https://julea-io.github.io/julea/structJBackend.html)
Is a union of `object`, `kv` and `db`. Each of these structures has only pointers to functions in its fields. \
Set of functions in `object` structure: `backend_init`, `backend_fini`, `backend_create`, `backend_open`,
`backend_delete`, `backend_close`, `backend_status`, `backend_status`, `backend_sync`, `backend_read`, 
`backend_write`, `backend_get_all`, `backend_get_by_prefix` and `backend_iterate`.
I didn't find clear explanations of their semantics, 
thus I can only guess that they should do something similar to standard filesystems
 (like those implemented with futex). \
**Question 1:** should I implement those functions using open-io C-language API? \
**Question 2:** how is it connected to already existing part of JULEA? 
Should my part of project use smth from there or is it completely independent from other backends? \



