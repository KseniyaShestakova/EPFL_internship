## Object filesystems
#### [The idea of object filesystems](https://en.wikipedia.org/wiki/Object_storage):
Each object usually contains data, metadata and a global unique identifier 
(see `index` in fields of Julea data structures). Does not keep structure. 
Is useful when data is unstructured, written once and read once.
Opposite to [hierarchical filesystems](https://en.wikipedia.org/wiki/Hierarchical_file_system) (usually tree-structured, like in Linux) and [block storage](https://en.wikipedia.org/wiki/Block_(data_storage)).

## Meson
### Build system aiming to facilitate build and compiling 
Uses ninja, an underlying build system designed for fast compiling and build.

[Quick start guide for meson](https://mesonbuild.com/SimpleStart.html) \
[Tutorial for meson with example](https://mesonbuild.com/Tutorial.html)

## Julea
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



  
