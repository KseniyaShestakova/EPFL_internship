## Object filesystems
#### [The idea of object filesystems](https://en.wikipedia.org/wiki/Object_storage):
Each object usually contains data, metadata and a global unique identifier 
(see `index` in fields of Julea data structures). Does not keep structure. 
Is useful when data is unstructured, written once and read once.
Opposite to [hierarchical filesystems](https://en.wikipedia.org/wiki/Hierarchical_file_system) (usually tree-structured, like in Linux) and [block storage](https://en.wikipedia.org/wiki/Block_(data_storage)).

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
* *consistency* - if and when clients will see modifications made by other clients (for client-side read caching, for example)
* *ordering* - how operations can be reordered for optimizing
* *persistency* - if and when metadata must be written to persistent storage (for client-side write caching, for example)
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

### Questions:
1. What is enzo in the plan? 
2. *Julea has a tool to gather server statistics*. What should I use to measure performance?
3. *Clients provide interfaces that can be used by applications or other I/O libraries.* How do clients provide those interfaces? (3.1)




  
