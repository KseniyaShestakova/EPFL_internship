#include "client.h"

#include <string.h>


struct BackendData {
    minio::s3::BaseUrl base_url;
    minio::creds::StaticProvider provider;
    minio::s3::Client client;

    BackendData(const std::string& path,
                const std::string& login = "minioadmin",
                const std::string& password = "minioadmin") :
            base_url(path),
            provider(login, password),
            client(base_url, &provider) {}

};

struct BackendObject {
    std::string bucket;
    std::string object;
    uint64_t refCount;

    BackendObject(const std::string& bucket, const std::string& object) :
        bucket(bucket), object(object), refCount(1) {}
};

void increaseRefCount(BackendObject* bo) {
    ++(bo->refCount);
}

void decreaseRefCount(BackendObject* bo) {
    --(bo->refCount);
}

std::unordered_map<std::string, BackendObject*> handler;

std::string get_path(const std::string& bucket, const std::string& object) {
    return bucket + ";" + object;
}

struct BackendIterator {
    minio::s3::ListObjectsResult current;
    bool is_valid;

    BackendIterator(minio::s3::Client* client,
                    const minio::s3::ListObjectsArgs& args) : 
                    current(client, args),
                    is_valid(*current) {}

};

BackendIterator* iterator_new(minio::s3::Client* client,
                              const minio::s3::ListObjectsArgs& args) {
    auto it = new BackendIterator(client, args);

    return it;
}

void iterator_free(BackendIterator* it) {
    delete it;
}

void iterator_next(BackendIterator* it) {
    if (!(it->is_valid)) {
        return;
    }

    ++(it->current);

    it->is_valid = it->current && *(it->current);
}

void iterator_get(BackendIterator* it, std::string& name) {
    name = (it->is_valid) ? (*(it->current)).name : "";
}

bool create_without_check(BackendData* bd, const std::string& bucket,
                                           const std::string& object,
                                           BackendObject** bo,
                                           const std::string& path) {
    //TODO: may be it could be simplified?...
    std::istringstream str("");

    minio::s3::PutObjectArgs args(str, 0, 0);
    args.bucket = bucket;
    args.object = object;

    minio::s3::PutObjectResponse resp = (bd->client).PutObject(args);

    if (resp) {
        std::cout << "Added " << object << " to " << bucket << std::endl;
    } else {
        std::cout << "Error: PutObject: " << resp.Error().String() << std::endl;
        return false;
    }

    *bo = new BackendObject(bucket, object);

    if (*bo == nullptr)
        return false;

    auto it_bool_pair = handler.emplace(path, *bo);

    return it_bool_pair.second;
}

bool exists(BackendData* bd, const std::string& bucket, const std::string& object) {
    minio::s3::GetObjectArgs args;
    args.bucket = bucket;
    args.object = object;

    args.datafunc = [](minio::http::DataFunctionArgs args) -> bool {
        return true;
    };

    minio::s3::GetObjectResponse resp = (bd->client).GetObject(args);

    return resp;
}

bool create_or_open(BackendData* bd, const std::string& bucket,
                                     const std::string& object,
                                     BackendObject** bo,
                                     bool non_create) {
    if (*bo != nullptr) {
        std::cerr << "You are about to lose existing object handler!" << std::endl;
        return false;
    }

    std::string path = get_path(bucket, object);

    auto it = handler.find(path);

    if (it != handler.end()) {
        if (non_create) {
            increaseRefCount((*it).second);
            *bo = (*it).second;
        }
        return non_create;
    }

    if (exists(bd, bucket, object)) {
        if (non_create) {
            *bo = new BackendObject(bucket, object);
            return handler.emplace(path, *bo).second;
        }
        return non_create;
    }

    return create_without_check(bd, bucket, object, bo, path);
}

bool create(BackendData* bd, const std::string& bucket,
                             const std::string& object,
                             BackendObject** bo) {
    return create_or_open(bd, bucket, object, bo, false);
}

bool open(BackendData* bd, const std::string& bucket,
                           const std::string& object,
                           BackendObject** bo) {
    return create_or_open(bd, bucket, object, bo, true);
}

bool close(BackendData* bd, BackendObject* bo) {
    (void)bd;
    std::string path = get_path(bo->bucket, bo->object);

    auto it = handler.find(path);

    if (it == handler.end()) {
        std::cout << "Not found" << std::endl;
        return false;
    }

    decreaseRefCount((*it).second);

    if ((*it).second->refCount <= 0) {
        delete bo;
        size_t num_erased = handler.erase(path);
        return num_erased == 1;
    }

    return true;
}

bool delete_object(BackendData* bd, const std::string& object,
                                    const std::string& bucket) {
    minio::s3::RemoveObjectArgs args;
    args.bucket = bucket;
    args.object = object;

    minio::s3::RemoveObjectResponse resp = (bd->client).RemoveObject(args);

    if (resp) {
        std::cout << "Deleted " << object << " from " << bucket << std::endl;
        return true;
    }
    std::cout << "Error: RemoveObject: " << resp.Error().String() << std::endl;
    return false;
}

bool delete_object(BackendData* bd, BackendObject* bo) {
    std::string path = get_path(bo->bucket, bo->object);

    auto it = handler.find(path);

    if (it == handler.end()) {
        std::cout << "Not found" << std::endl;
        return false;
    }

    if ((*it).second->refCount > 1) {
        std::cout << "Many links, can't delete: " <<
            (*it).second->refCount << std::endl;
        return false;
    }

    if (it == handler.end() || (*it).second->refCount > 1) {
        return false;
    }

    // delete an object
    delete_object(bd, bo->object, bo->bucket);

    // delete from unordered map
    delete bo;
    size_t num_erased = handler.erase(path);
    return num_erased == 1;
}

bool status(BackendData* bd, BackendObject* bo,
            int64_t* modification_time, uint64_t* size) {
    minio::s3::StatObjectArgs args;
    args.bucket = bo->bucket;
    args.object = bo->object;

    minio::s3::StatObjectResponse resp = (bd->client).StatObject(args);

    if (resp) {
        *modification_time = resp.last_modified;
        *size = resp.size;
        return true;
    }
    std::cout << "Error: Stat: " << resp.Error().String() << std::endl;
    return false;
}

bool read(BackendData* bd, BackendObject* bo,
          char* buffer,
          uint64_t length, uint64_t offset,
          uint64_t* bytes_read) {
    minio::s3::GetObjectArgs args;
    args.bucket = bo->bucket;
    args.object = bo->object;
    //TODO: somehow putting offset and length changes nothing
    args.offset = &offset;
    args.length = &length;

    std::cout << "offset: " << *(args.offset)
        << "; length: " << *(args.length) << std::endl;

    uint64_t total = 0;
    args.datafunc = [&](minio::http::DataFunctionArgs args) -> bool {
        /* args.datachunk is a string */
        memcpy(buffer + total, args.datachunk.c_str(), args.datachunk.size());
        total += args.datachunk.size();
        return true;
    };

    minio::s3::GetObjectResponse resp = (bd->client).GetObject(args);

    std::cout << "offset: " << *(args.offset)
         << "; length: " << *(args.length) << std::endl;

    if (!resp) {
        std::cout << "Error: GetObject: " << resp.Error().String() << std::endl;
        return false;
    }
    *bytes_read = total;
    return true;
}

bool write(BackendData* bd, BackendObject* bo,
           const char* buffer,
           uint64_t length, uint64_t offset,
           uint64_t* bytes_written) {
    std::stringstream str;
    str.write(buffer, length);

    minio::s3::PutObjectArgs args(str, length, 0);
    args.bucket = bo->bucket;
    args.object = bo->object;

    minio::s3::PutObjectResponse resp = (bd->client).PutObject(args);

    if (!resp) {
        std::cout << "Error: PutObject: " << resp.Error().String() << std::endl;
        return false;
    }

    return true;
}

bool get_list(BackendData* bd, const std::string& bucket,
              BackendIterator** bi,
              const std::string& prefix = "") {
    minio::s3::ListObjectsArgs args;
    args.bucket = bucket;
    args.prefix = prefix;

    *bi = iterator_new(&(bd->client), args);

    return *bi != nullptr;
}

bool get_all(BackendData* bd,
             const std::string& ns,
             BackendIterator** bi) {
    return get_list(bd, ns, bi);
}

bool get_by_prefix(BackendData* bd,
                   const std::string& ns,
                   BackendIterator** bi,
                   const std::string&  prefix) {
    return get_list(bd, ns, bi, prefix);
}

bool iterate(BackendData* bd, BackendIterator* bi, std::string& name) {
    (void)bd;

    iterator_get(bi, name);

    iterator_next(bi);

    return (name != "");
}

bool init(const std::string& path, BackendData** bd) {
    if (*bd != nullptr) {
        std::cerr << "You're trying to reuse existing BackendData pointer!";
        return false;
    }
    *bd = new BackendData(path);

    return *bd != nullptr;
}

void fini(BackendData* bd) {
    if (bd != nullptr) {
        delete bd;
    }
}
/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

bool create_namespace(BackendData* bd,
                  const std::string& bucket_name) {
    minio::s3::MakeBucketArgs args;
    args.bucket = bucket_name;
 
    minio::s3::MakeBucketResponse resp = (bd->client).MakeBucket(args);

    if (resp) {
        std::cout << bucket_name << " was created" << std::endl;
        return true;
    }
    std::cout << "unable to create " << bucket_name <<
        resp.Error().String() << std::endl;
    return false;
}

bool delete_bucket(BackendData* bd, const std::string& bucket) {
    minio::s3::RemoveBucketArgs args;
    args.bucket = bucket;

    minio::s3::RemoveBucketResponse resp = (bd->client).RemoveBucket(args);

    if (resp) {
        std::cout << bucket << " was removed successfully" << std::endl;
        return true;
    }

    std::cout << "Error:  RemoveBucket: " << resp.Error().String() << std::endl;
    return false;
}

bool clean_namespace(BackendData* bd, const std::string& bucket,
        const std::string& prefix = "") {
    BackendIterator* bi = nullptr;
    get_all(bd, bucket, &bi);

    std::string name;
    while (iterate(bd, bi, name)) {
        std::cout << "deleting " << name << "..." << std::endl;
        bool ret = delete_object(bd, name, bucket);
        if (!ret) {
            return false;
        }
    }

    iterator_free(bi);

    if (prefix != "") {
        bi = nullptr;
        get_by_prefix(bd, bucket, &bi, prefix);
        
        while (iterate(bd, bi, name)) {
            std::cout << "deleting " << name << "..." << std::endl;
            bool ret = delete_object(bd, name, bucket);
            if (!ret) {
                return false;
            }
        }

        iterator_free(bi);

    }

    return delete_bucket(bd, bucket);
}

/*
int main() {
    BackendData* bd = nullptr;
    init("play.min.io", &bd);

    //make_bucket(bd, "tmp-bucket-5");
    BackendObject* bo;
    char buffer[] = "content";
    uint64_t bytes_written = 0;

    if (!exists(bd, "tmp-bucket-5", "strange_object.txt")) {
      //  create_namespace(bd, "tmp-bucket-5");
    }
    create_without_check(bd, "tmp-bucket-5", "obj1.txt", &bo, "path1");
    write(bd, bo, buffer, 7, 0, &bytes_written);
    std::cout << "written " << bytes_written << " bytes" << std::endl;
    //create_without_check(bd, "tmp-bucket-5", "obj2.txt", &bo, "path2");
    //create_without_check(bd, "tmp-bucket-5", "foo.txt", &bo, "path3");

    BackendIterator* bi = nullptr;
    get_by_prefix(bd, "tmp-bucket-5", &bi, "obj");
    std::string name;
    uint64_t cnt = 0;

    while(iterate(bd, bi, name)) {
        std::cout << name << std::endl;
        ++cnt;
    }
    std::cout << cnt << " objects total" << std::endl;
    //delete_object(bd, "obj1.txt", "tmp-bucket-5");
    
    char read_buffer[256];
    uint64_t bytes_read = 0;
    read(bd, bo, read_buffer, 5, 2, &bytes_read);
    std::cout << "read " << bytes_read << " bytes" << std::endl;
    read_buffer[bytes_read] = 0;
    std::cout << "Read: " << read_buffer << std::endl;

    int64_t modification_time = -1;
    uint64_t size = -1;
    status(bd, bo, &modification_time, &size);
    std::cout << "Mod.time: " << modification_time << "; size: " << size << std::endl;
    clean_namespace(bd, "tmp-bucket-5");

    fini(bd);

}*/
