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

    BackendObject(const std::string& bucket, const std::string& object) :
        bucket(bucket), object(object) {}
};

bool create_without_check(BackendData* bd, const std::string& bucket,
                                           const std::string& object,
                                           BackendObject** bo) {
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
    return *bo != nullptr;
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
    args.offset = &offset;
    args.length = &length;

    uint64_t total = 0;
    args.datafunc = [&](minio::http::DataFunctionArgs args) -> bool {
        /* args.datachunk is a string */
        memcpy(buffer + total, args.datachunk.c_str(), args.datachunk.size());
        total += args.datachunk.size();
        return true;
    };

    minio::s3::GetObjectResponse resp = (bd->client).GetObject(args);

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

int main() {
    BackendData* bd = nullptr;
    init("play.min.io", &bd);

    //make_bucket(bd, "tmp-bucket-5");
    BackendObject* bo;
    create_without_check(bd, "tmp-bucket-5", "obj1.txt", &bo);
    create_without_check(bd, "tmp-bucket-5", "obj2.txt", &bo);
    delete_object(bd, "obj1.txt", "tmp-bucket-5");
    int64_t modification_time = -1;
    uint64_t size = -1;
    status(bd, bo, &modification_time, &size);
    std::cout << "Mod.time: " << modification_time << "; size: " << size << std::endl;

    fini(bd);

}
