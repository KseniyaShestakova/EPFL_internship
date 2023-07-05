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
 Maybe compared to [BlueStore project](https://github.com/Bella42/julea/blob/objectstore/bluestore/julea_bluestore.h) \
**Question 1:** should I implement those functions using open-io C-language API? \
**Question 2:** how is it connected to already existing part of JULEA? 
Should my part of project use smth from there or is it completely independent from other backends? \
**Question 3:** how is the project connected to SDDFs like HDF-5?


### Open-IO
[Running a docker container with OpenIO](https://docs.openio.io/latest/source/sandbox-guide/docker_image.html) 

```
docker pull openio/sds:20.04                                     # pulls an image
docker run --name oio-sds openio/sds:20.04                       # runs it
docker inspect -f '{{ .NetworkSettings.IPAddress }}' oio-sds     # retrieves container's IP
```
using openio client in the docker instance. These commands open a command line where openio is available.
```
docker ps
docker exec -it <container_ID> bash
[root@9fad98f2a968 /]# openio help
```

[C API instructions](https://docs.openio.io/latest/source/sdk-guide/c_example.html) - clonning from this instruction didn't work \
[Github repository](https://github.com/open-io/oio-sds) \
[Quick Start](https://docs.openio.io/latest/source/sandbox-guide/quickstart.html)




