## Object filesystems
#### [The idea of object filesystems](https://en.wikipedia.org/wiki/Object_storage):
Each object usually contains data, metadata and a global unique identifier 
(see `index` in fields of Julea data structures). Does not keep structure. 
Is useful when data is unstructured, written once and read once.
Opposite to [hierarchical filesystems](https://en.wikipedia.org/wiki/Hierarchical_file_system) (usually tree-structured, like in Linux) and [block storage](https://en.wikipedia.org/wiki/Block_(data_storage)).
#### Something interesting from Survey of Storage Systems for High-Performance Computing:
Parallel distributed file systems are used for hot data (being accesses immediately after being created, or very frequently) and [tape archives](https://en.wikipedia.org/wiki/Tape_drive) are used for cold data (rarely accessed). \
[Memory wall problem](https://developer20.com/memory-wall-problem/) - occurs when the speed of processor executing instructions is significantly higher than the speed of writing and reading data from memory. \
**Data storages:**
* *tapes* - the most common cold storage technology: cheap, reliable, with long retention time and capacity,
  no energy is required for inactive media. Provides sequential access, thus is inappropriate for hot data
* *HDD (Hard Disk Drives)* - dominating storage technology, reliable and with competitive price. Stores data on magnetic coating of rotating platters, with actuator arm, placing the read/write head on different locations of the disc.
* *SSD (Solid-State Drivers)* - are used to improve small random access I/O performance.
* *NVRAM (Non-Volatile Random-Access Memory)* - retains data when powered off: flash memory and phase-change memory
* *VRAM*: *SRAM (Static RAM)* and *DRAM (Dynamic RAM)*. Is used to accelerate access to data that is currently in use or anticipated to be used soon. 
**File systems:**
* *Spectrum Scale* - scalable, HPC, very capable, supported by IBM with various useful tools, but very expensive. Based on General Parallel File System.
* *Lustre* - parallel distributed kernel-space filesystem used on supercomputers under GNU General Public License. Has distinct architectures for clients and servers (Metadata Servers and Object Storage Servers)
* *BeeGFS* - parallel and POSIX-compliant cluster filesystem for intensive HPC applications
* *OrangeFS* - parallel distributed completely user-space fs
* *IBIO* - a user-level file system designed as an internal layer between compute nodes and parallel file system.
* *GlusterFS* - POSIX-compliant, free and open-source distributed filesystem 

## Meson
### Build system aiming to facilitate build and compiling 
Uses ninja, an underlying build system designed for fast compiling and build. Runs completely in user space.

[Quick start guide for meson](https://mesonbuild.com/SimpleStart.html) \
[Tutorial for meson with example](https://mesonbuild.com/Tutorial.html)

## Julea
Not actually an object store, because objects are mapped to files in underlying filesystem.
### Understanding Kuhn's paper about Julea
[SDDF](https://www.gartner.com/en/information-technology/glossary/self-describing-messages#:~:text=A%20message%20that%20contains%20data,consists%20of%20tag%2Fvalue%20pairs.) - self describing data formats - the message, containg both data and metadata. Thus, structure and meaning (syntax and semantics) are described simultaneously.

Monolitic filesystems are too inflexible for research and teaching.
So, for getting more comprehensive understanding of filesystems, there are developed frameworks that are
extensible using plugins for AFI, stortage backend and semantics.

Many applications access filesystems not directly but via high-level libraries. 
Multiple projects try to solve the problem (of flexibility and performance) by integrating filesystems and I/O libraries more closely.

Julea is a flexible storage framework for prototyping new approaches in research and teaching.gn 

**Goals and design**: triple model: metadata server + client + data server.
Client and server communicate via the network.
Supporting multiple backends allows to use multiple existing storage technologies and foster experimentation.
Client interfaces can bechanged easily.
Backend: `create` and `open` return an object handle on success, `delete` and `close` destroy the handle. `status` provide object modification time and size.
Batchs allow aggregating multiple put and delete operations to improve performance.

**Semantics:**
* *atomicity* - if required, there will a lock for hiding inermediate states of operations
* *concurrency* - to manage concurrent access patterns
* *consistency* - if and when clients will see modifications made by other clients (e.g. for client-side read caching)
* *ordering* - how operations can be reordered for optimizing
* *persistency* - if and when metadata must be written to persistent storage (e.g. for client-side write caching)
* *safety* - guarantees about the state of data and metadate

**Clients** provide interfaces with separate namespace in order not to interfere with each other:
* *object* - direct access to JULEA's data store and arbitrary namespaces
* *kv* - direct access to JULEA's metadata store and arbitrary namespaces. Abstraction for key-value pairs
* *item* - cloud-like intrface with items and collections; collections can contain only items; collections and items can be listed using iterators
* *posix* - implements a posix filesystem using fuse framework

**Backends** determine how data and metadata operations are handled:
* *posix* - compatibility with existing POSIX filesystem
* *gio* - server-side data backend using [GIO library](https://docs.gtk.org/gio/)
* *lexos* - server-side data backend using LEXOS to provide a light-weight data store
* *null* server-side data backend intended for performance measurements
* *leveldb* - server-side metadata backend uses [LevelDB](https://github.com/google/leveldb) (storage mapping string keys to string values) for metadata storage
* *mongodb* - uses [MongoDB](https://en.wikipedia.org/wiki/MongoDB) and maps key-value pairs to documents using appropriate indexes

Performance depends a lot on the backends used.

### Understanding BlueStore_Julea
[Ceph](https://en.wikipedia.org/wiki/Ceph_(software)) - self-healing and self-managing storage platform, providing object storage, block storage and file storage based on distributed cluster foundation. \
[Ceph OSD](https://docs.ceph.com/en/latest/man/8/ceph-osd/) - object storage daemon for the Ceph distributed file system. \
[BlueStore](https://docs.ceph.com/en/latest/rados/configuration/storage-devices/) - special-purpose storage backend for managing data on disk for Ceph OSD workloads. \
Complexities: hierarchy of different storage hardware, software stack. Separation between individual layers allows to exchange them easily, but it causes performance and management issues. \
I/O libraries such as NetCDF, HDF5, ADIOS are used to make data handking easierfor the applivation developers and users. \
Structured information (lie filesystem metadata) is stored  in key-value stores, while unstructured data (like file content) is stored in object stores. \
[NoSQL database](https://www.mongodb.com/nosql-explained) - not relational one. \
[Dual access](https://doi.org/10.1145/3357223.3362703) - the ability to write and read the same data through file systems interfaces and object storage APIs. Is argued to be required to satisfy all current demands.\
**Notes about evaluation:**
* *hardware description* - description of processor, main memory capacity, HDD capacity and throughput
  measuring throughput of one's computer:
  ```
  dd if=/dev/zero of=test.jpg bs=4k count=1000 oflag=sync
  dd if=/dev/zero of=~/Downloads/IMG_20210210_102428.jpg bs=1G count=1 oflag=dsync
  ```
  for a detailed description see `man dd`
* *software description* - OS+Kernel, Ceph and JULEA version, compiler
* *evaluation* - measurements were formed for different duration (1 to 512s) to rule out variability over time, and for different block sizes. Set `storage=safety` to avoid measuring only cache (every operation will be synced to the HDD). Batched operations should be evaluated with sync performed after every n-th operation, depending on the block size.



### Understanding `julea/example/hello-world.c`
Can be run via:
```console
cd example/
make run
```
Outputs logs and content of files in created filesystem (?)
#### Includes:
* `julea.h` - the list of includes from `lib/core/` directory
* `julea-object.h` - the list of includes from `lib/object/` directory
* `julea-kv.h` - the list of includes from `lib/kv/` directory, kv means 'key-value'
* `julea-db.h` - the list of includes from `lib/db/` directory, db means 'database'
* `locale.h` - c-header file for managing location-specific data, like time and currency
* `stdio.h`

#### Functions, data structures and etc. :
* `g_autopr` - macro that declares a pointer of specified type and registers a function that will delete object
   when the pointer goes out of scope
*  [`JList`](https://julea-io.github.io/julea/structJList.html) - a linked list, fields: head, tail, length, free_func, ref_count
*  [`JSemantics`](https://julea-io.github.io/julea/structJSemantics.html) - describes semantics of the bactch: atomicity of batched operations,
    consistency (describes when other clients are able to read written data: immediate, session, eventual),
    persistency (guarantees on persistency of finished operations),
   security (currently unused) : strict or none, immutability, ref_count
* [`JBackgroundOperation`](https://julea-io.github.io/julea/structJBackgroundOperation.html) - a bacckground operation, fields: func, data (gpointer), result (gpointer),
   completed (gboolean), mutex, cond, ref_count
* [`JBatch`](https://julea-io.github.io/julea/structJBatch.html) - an operation, fields: background_operation, list of pending operations, ref_count, semantics
* `bson` - binary json
*  [`JDBSchema`](https://julea-io.github.io/julea/structJDBSchema.html) - fields: bson, bson_index (bson_t),
   variables (hash table), index (array), bson_index_count, ref_count, bson_initialized, bson_index_initialized,
   server_side (booleans) - emulates db-schema probably
* [`JDBEntry`](https://julea-io.github.io/julea/structJDBEntry.html) - entry of a database, fields: bson, id,
  schema (JDBSchema*), ref_count
* [`JKV`](https://julea-io.github.io/julea/structJKV.html) - a key-value pair, fields: guint index, gchar* key, ref_count
* [`JObject`](https://julea-io.github.io/julea/structJObject.html) - fields: index, name, ref_count

`index` is a data server index.
* [`j_batch_new_for_template`](https://julea-io.github.io/julea/group__JBatch.html#ga4bcf3b687f3b4efdf713ea0e7955e9e2)
* [`j_object_new`](https://julea-io.github.io/julea/group__JObject.html),
 [`j_kv_new`](https://julea-io.github.io/julea/group__JKV.html#gabac1e064643e3f6cf9ca25f0f5c492f0) - constructs an object, kv
  from namespace and name, key
*  `j_kv_put` - actually makes a new operation and adds it to the batch, this operation handles current kv and value

### Open-IO
A software-defined object store.

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

[C API instructions](https://docs.openio.io/latest/source/sdk-guide/c_example.html)  \
[Github repository](https://github.com/open-io/oio-sds) \
[Quick Start](https://docs.openio.io/latest/source/sandbox-guide/quickstart.html)

What can be understood from [OpenIO End-User CLI](https://docs.openio.io/latest/source/user-guide/openiocli.html#ref-user-guide): \
OpenIO CLI (command line interface) supports the next abstractions:
* **accounts** track usage about storages; are usually automatically created though manual creation is also possible. Sample requests:
```
openio account create my_account     # creates a new account
openio account show my_account       # shows info (number of containers, objects, etc.) about an account
```
* **containers** are used to store objects
```
openio container create my_container --oio-account my_account
openio container show my_container
openio container locate my_container                    # to find services used by a given container
openio container set my_container --property color=blue # to set a property (like metadata)
openio container unset my_container --property color    # to unset a property
openio container delete my_container                    # only empty containers can be deleted

```
* **objects** are alternative for files in classical filesystems
```
openio object create my_container existing_file.txt   # creating object from a file
openio object list my_container                       # list of objects in my_container
 ```
Ouput of `openio object list` can be filtered with: `--limit n` - shows a maximum of `n` objects,
`--marker e` shows only objects whose names are lexically greater than e, `--prefix pref`  shows only objects whose names begin with `pref`, `--delimiter _` excludes all the objects whose names contain a `_`. \
Objects can be saved to files
```
openio object save my_container test.txt --file /dest/test.txt
mkdir test_folder && cd test_folder
openio container save my_container                              # saves all the objects from a container
```
`show`, `locate`, `--property`, `delete` are applicable to objects just like to the containers.
* **clusters (or namespaces)**
```
openio cluster show                       # display the namespace configuration
openio cluster list                       # display all known services
openio cluster list rawx meta2            # list only specific types of services
openio cluster local conf                 # display cluster local configuration
openio cluster unlock raw 127.0.0.1:6015  # unlock a new service
openio cluster unlockall                  # unlock all registred services
```
### Building OpenIO from Github repository
OpenIO seems to be correctly supported only by Ubuntu 18.04, thus one will probably need either docker or virtual machine for running it. \
I've downloaded docker image with Ubuntu 18.04 and ran a shell inside it. [This one](https://lynxbee.com/how-to-run-ubuntu-18-04-in-docker-container/), probably. \
[How to save/commit changes to docker image?](https://lynxbee.com/how-to-save-commit-changes-to-docker-image/) - needs to be seen, because installation of all the dependencies wad rather long!!! \
[A guide](https://docs.openio.io/latest/source/sandbox-guide/build_from_source.html) that should be followed inside a container. \
The rootshell of Ubuntu 18.04 needs to be started at this point. \
**Issues:**
* needs curl to be installed before configuring the repository: `apt install curl` or `apt-get install curl`
* `sudo apt -y install golang-go` installs golang with version 1.10, while at least 1.18 is required. Lower versions of go lead to compilation errors because the executed files contain some functions which were added in later versions (method #3 from [this article](https://www.cyberciti.biz/faq/how-to-install-gol-ang-on-ubuntu-linux/) finally worked for me)

After running all the instructions from the quide above I also ran cmake and make form [github](https://github.com/open-io/oio-sds/blob/master/BUILD.md), ran the test suit (almost all the test failed in my case). \
After that I noticed that in `oio-sds/core` there are files with shared libraries `liboiocore.so`, `liboiocore.so.0`, `liboiocore.so.0.0.0` and `liboiosds.so`, `liboiosds.so.0`, `liboiosds.so.0.0.0`.
 Reffering to the symbol table:
 ```
objdump -t liboiocore.so
```
suggests that these libraries contain functions from official C API, so linking them will probably help running a sample code and further developing JULEA's backend. 

Reference for linking shared libraries:
* [Example](https://www.baeldung.com/linux/library_path-vs-ld_library_path) of working with shared libraries
* [Quick introduction](https://linuxhint.com/what-is-ld-library-path/) to what is LD_LIBRARY_PATH

LD_LIBRARY_PATH is an environmental variable telling dynamic loader where to look for shared libraries (affects runtime).
LIBRARY_PATH affects `gcc` while linking.


  
