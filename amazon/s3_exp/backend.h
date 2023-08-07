#include <string.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/Bucket.h>
#include <aws/s3/model/CreateBucketRequest.h>
#include <aws/s3/model/BucketLocationConstraint.h>
#include <aws/s3/model/DeleteBucketRequest.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/s3/model/Object.h>
#include <aws/core/utils/UUID.h>
#include <aws/core/utils/StringUtils.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/s3/model/DeleteObjectRequest.h>

// C-style structs, no OOP
#include <glib.h>

void foo(gchar const* str) {
    Aws::String string = str;
    std::cout << str;
}

struct BackendData {
    std::string path = "127.0.0.1:9000";
    Aws::SDKOptions* options;
    Aws::S3::S3Client* client;
};

struct BackendObject {
    Aws::String bucket;
    Aws::String objectKey;
    uint64_t refCount = 0;
};

void increaseRefCount(BackendObject* bo) {
    ++(bo->refCount);
}

void decreaseRefCount(BackendObject* bo) {
    --(bo->refCount);
}

std::unordered_map<Aws::String, BackendObject*> handler;

//TODO: adopt for naming rules of amazon
Aws::String get_path(const Aws::String& bucket, const Aws::String& objectKey) {
    return bucket + ";" + objectKey;
}

struct BackendIterator {
    Aws::Vector<Aws::S3::Model::Object>* objects = nullptr;
    uint64_t pos = 0;
};

BackendIterator* iterator_new() {
    auto it = new BackendIterator;

    it->objects = nullptr;
    it->pos = 0;

    return it;
}

void iterator_free(BackendIterator* it) {
    if (it->objects != nullptr) {
        delete it->objects;
    }

    delete it;
}

void iterator_next(BackendIterator* it) {
    if (it->objects == nullptr) return;

    if (it->pos < (it->objects)->size()) {
        ++(it->pos);
    }
}

bool isValid(BackendIterator* it) {
    return (it->objects != nullptr) && (it->pos < (it->objects)->size());
}

void iterator_get(BackendIterator* it, std::string& name) {
    name =  isValid(it) ? (it->objects)->operator[](it->pos).GetKey() : "";
}

void fill_object(BackendObject** bo,
                 const Aws::String& bucket,
                 const Aws::String& object) {
    *bo = new BackendObject;
    (*bo)->bucket = bucket;
    (*bo)->objectKey = object;
    (*bo)->refCount = 1;
}

bool create_without_check(BackendData*bd, const Aws::String& bucket,
                                          const Aws::String& object,
                                          BackendObject** bo,
                                          const Aws::String& path) {
    Aws::S3::Model::PutObjectRequest request;
    request.SetBucket(bucket);
    request.SetKey(object);
 
    std::shared_ptr<Aws::IOStream> inputData =
         Aws::MakeShared<Aws::StringStream>("SampleAllocationTag", "");
 
    if (!*inputData) {
        std::cerr << "Error while creating shared_ptr" << std::endl;
        return false;
    }
 
    request.SetBody(inputData);
 
    Aws::S3::Model::PutObjectOutcome outcome = (bd->client)->PutObject(request);
 
    if (!outcome.IsSuccess()) {
        std::cerr << "Error: PutObject: " <<
            outcome.GetError().GetMessage() << std::endl;
        return false;
    } 
    std::cout << "Added object " << object << " to bucket " <<
            bucket << std::endl;
    fill_object(bo, bucket, object);
    auto it_bool_pair = handler.emplace(path, *bo);
    
    return it_bool_pair.second;
}

bool exists(BackendData* bd, const Aws::String& bucket, const Aws::String& object) {
    Aws::S3::Model::GetObjectRequest request;
    request.SetBucket(bucket);
    request.SetKey(object);

    Aws::S3::Model::GetObjectOutcome outcome =
            (bd->client)->GetObject(request);

    if (!outcome.IsSuccess()) {
        const Aws::S3::S3Error &err = outcome.GetError();
        if (err.GetExceptionName() == "NoSuchKey") {
            return false;
        }
        std::cerr << "Error: GetObject: " <<
                  err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        return true; //error should be handled somehow!
    }
    return true; 
}

bool create_or_open(BackendData* bd, const Aws::String& bucket,
                                     const Aws::String& object,
                                     BackendObject** bo,
                                     bool non_create) {
    if (*bo != nullptr) {
        std::cerr << "You are about to lose existing object handler!" << std::endl;
        return false;
    }

    Aws::String path = get_path(bucket, object);

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
            fill_object(bo, bucket, object);
            return handler.emplace(path, *bo).second;
        }
        return non_create;
    }
 
    return create_without_check(bd, bucket, object, bo, path);
}

bool create(BackendData* bd, const Aws::String& bucket,
                             const Aws::String& object,
                             BackendObject** bo) {
    return create_or_open(bd, bucket, object, bo, false);
}

bool open(BackendData* bd, const Aws::String&/*namespace*/ bucket,
                           const Aws::String&/*path*/ object,
                           BackendObject** bo) {
    return create_or_open(bd, bucket, object, bo, true);
}

bool close(BackendData* bd, BackendObject* bo) {
    (void)bd;
    Aws::String path = get_path(bo->bucket, bo->objectKey);

    auto it = handler.find(path);

    if (it == handler.end()) {
        std::cout << "Not found" << std::endl;
        return false;
    }

    decreaseRefCount((*it).second);

    if ((*it).second->refCount <= 0) {
        delete bo; // was allocated either in create or in open
        size_t num_erased = handler.erase(path);
        return num_erased == 1;
    }

    return true;
}

bool delete_object(BackendData* bd, const Aws::String& objectKey,
                                    const Aws::String& bucket) {
    Aws::S3::Model::DeleteObjectRequest request;

    request.SetBucket(bucket);
    request.SetKey(objectKey);

    Aws::S3::Model::DeleteObjectOutcome outcome = (bd->client)->DeleteObject(request);

    if (!outcome.IsSuccess()) {
        auto err = outcome.GetError();
        std::cerr << "Error: DeleteObject: " <<
                  err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        return false;
    }

    std::cout << "Successfully deleted " << objectKey << std::endl;
    return true;
}

// we cannot delete an object used by another process or thread
bool delete_object(BackendData* bd, BackendObject* bo) {
    Aws::String path = get_path(bo->bucket, bo->objectKey);

    auto it = handler.find(path);

    if (it == handler.end()) {
        std::cout << "Not found in the map" << std::endl;
        return false;
    }

    if ((*it).second->refCount > 1) {
        std::cout << "Many links, can't delete: "
            << (*it).second->refCount << std::endl;
        return false;
    }

    if (it == handler.end() || (*it).second->refCount > 1) {
        return false;
    }

    // delete an object
    delete_object(bd, bo->objectKey, bo->bucket);

    // delete from unordered map
    delete bo;
    size_t num_erased = handler.erase(path);
    return num_erased == 1;
 }


bool status(BackendData* bd, BackendObject* bo,
            int64_t* modification_time, uint64_t* size) {
    Aws::S3::Model::GetObjectRequest request;
    request.SetBucket(bo->bucket);
    request.SetKey(bo->objectKey);

    Aws::S3::Model::GetObjectOutcome outcome = (bd->client)->GetObject(request);

    if (!outcome.IsSuccess()) {
        const Aws::S3::S3Error& err = outcome.GetError();
        std::cerr << "Error: GetObject: " <<
                  err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        return false;
    }

    Aws::S3::Model::GetObjectResult& result = outcome.GetResult();

    *size = result.GetContentLength();

    const Aws::Utils::DateTime& last_modified = result.GetLastModified();

    *modification_time = last_modified.Millis();

    return true;
}

bool read(BackendData* bd, BackendObject* bo,
          char* buffer,
          uint64_t length, uint64_t offset,
          uint64_t* bytes_read) {
    Aws::S3::Model::GetObjectRequest request;
    request.SetBucket(bo->bucket);
    request.SetKey(bo->objectKey);

    std::string range = "bytes=";
    range += std::to_string(offset);
    range += "-";
    range += std::to_string(offset + length);

    request.SetRange(range);

    Aws::S3::Model::GetObjectOutcome outcome = (bd->client)->GetObject(request);
    if (!outcome.IsSuccess()) {
        auto err = outcome.GetError();
        std::cerr << "Error: GetObject: " << err.GetExceptionName() <<
            ": " << err.GetMessage() << std::endl;
        return false;
    }

    Aws::S3::Model::GetObjectResult& result = outcome.GetResult();
    Aws::IOStream& stream = result.GetBody();

    stream.read(buffer, length);
    *bytes_read = stream.gcount();

    return true;    
}

// can only rewrite the object with specified content
// buffer should be convertible to std::string
bool write(BackendData* bd, BackendObject* bo,
           const char* buffer,
           uint64_t length, uint64_t offset,
           uint64_t* bytes_written) {
    (void)offset; // ignored

    Aws::S3::Model::PutObjectRequest request;
    request.SetBucket(bo->bucket);
    request.SetKey(bo->objectKey);
    request.SetContentLength(length);

    std::shared_ptr<Aws::IOStream> inputData = 
        Aws::MakeShared<Aws::StringStream>("SampleAllocationTag", buffer);

    if (!*inputData) {
        std::cerr << "Error while creating shared ptr" << std::endl;
        return false;
    }

    request.SetBody(inputData);

    Aws::S3::Model::PutObjectOutcome outcome = (bd->client)->PutObject(request);

    if (!outcome.IsSuccess()) {
        auto err = outcome.GetError();
        std::cerr << "Error: PutObject: " << err.GetExceptionName() <<
            ": " << err.GetMessage() << std::endl;
        return false;
    }

    *bytes_written = inputData->gcount();

    return true;
    
}


bool get_list(BackendData* bd, const  Aws::String& bucket,
        BackendIterator** bi,
        const Aws::String& prefix = "") {
    *bi = iterator_new();

    if (*bi == nullptr) {
        return false;
    }

    Aws::S3::Model::ListObjectsRequest request;
    request.SetBucket(bucket);
    request.SetPrefix(prefix);

    auto outcome = (bd->client)->ListObjects(request);

    if (!outcome.IsSuccess()) {
        auto& err = outcome.GetError();
        std::cerr << "Error: ListObjects: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        return false;
    }

    (*bi)->objects = 
        new Aws::Vector<Aws::S3::Model::Object>(outcome.GetResult().GetContents());
    (*bi)->pos = 0;

    return true;
}

bool get_all(BackendData* bd,
             const std::string& /*namespace*/ns,
             BackendIterator** bi) {
    return get_list(bd, ns, bi);
} 

bool get_by_prefix(BackendData* bd,
                   const std::string&/*namespace*/ ns,
                   BackendIterator** bi,
                   const std::string& prefix) {
    return get_list(bd, ns, bi, prefix);
}

bool iterate(BackendData* bd, BackendIterator* bi, std::string& name) {
    (void)bd;

    iterator_get(bi, name);

    iterator_next(bi);

    return (name != "");
}



// default value of path = "127.0.0.1:9000"
bool init(const std::string& path, BackendData** bd) {
    *bd = new BackendData;

    if (*bd == nullptr) {
        return false;
    }

    (*bd)->path = path;

    (*bd)->options = new Aws::SDKOptions;
    Aws::InitAPI(*((*bd)->options));


    Aws::Client::ClientConfiguration cfg;
    cfg.endpointOverride = path;
    cfg.scheme = Aws::Http::Scheme::HTTP;
    cfg.verifySSL = false;

    (*bd)->client = new Aws::S3::S3Client(
            Aws::Auth::AWSCredentials("minioadmin", "minioadmin"),
                       cfg,
                       Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never,
                       false);

    return true;
}

void fini(BackendData* bd) {
    if (bd == nullptr) return;

    if (bd->options != nullptr)     
        Aws::ShutdownAPI(*(bd->options));

    if (bd->options != nullptr) 
        delete bd->options;
    if (bd->client != nullptr)  
        delete bd->client;

    delete bd;
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
 */

void manual_test() {
    std::string path = "127.0.0.1:9000";
     BackendData* bd = nullptr;
     init(path, &bd);
 
     BackendObject* bo = nullptr;
     open(bd, "test-bucket", "new.txt", &bo);
 
     uint64_t bytes_read = 0;
     uint64_t bytes_written = -1;
     char buffer[256];
     write(bd, bo, "hello", 5, 0, &bytes_written);
     read(bd, bo, buffer, 100, 0, &bytes_read);
     buffer[bytes_read] = 0;
     std::cout << "Read " << bytes_read << " bytes: " << buffer << std::endl;
 
 
     int64_t modification_time = 0;
     uint64_t size = -1;
     status(bd, bo, &modification_time, &size);
 
     std::cout << "size: " << size << "; modification time: " <<
             modification_time << std::endl;
 
     BackendObject* inspect = nullptr;
     open(bd, "test-bucket", "test.txt", &inspect);
     status(bd, inspect, &modification_time, &size);
     std::cout << "size: " << size << "; modification time: " <<
              modification_time << std::endl;

     read(bd, inspect, buffer, size, 3, &bytes_read);
     buffer[bytes_read] = 0;
     std::cout << "Read " << bytes_read << " bytes: " << buffer << std::endl;

     BackendIterator* bi;
     get_all(bd, "test-bucket", &bi);

     std::string name;

     std::cout << "List of elements in test-bucket:\n";
     while (iterate(bd, bi, name)) {
         std::cout << name << std::endl;
     }

     get_by_prefix(bd, "test-bucket", &bi, "te");

     std::cout << "\nList of elements with prefix `te` in test-bucket:\n";
     while(iterate(bd, bi, name)) {
         std::cout << name << std::endl;
     }


     delete_object(bd, bo);

     fini(bd);

}


void existence_test() {
    std::string path = "127.0.0.1:9000";
    BackendData* bd = nullptr;
    init(path, &bd);


    BackendObject* new_bo = nullptr;
    // should be 0, cause new.txt exists
    std::cout << "Create new.txt: "
        << create(bd, "test-bucket", "new.txt", &new_bo) << std::endl;

    BackendObject* old_bo = nullptr;
    // should be 0, cause test.txt exists
    std::cout << "Create test.txt: " 
        << create(bd, "test-bucket", "test.txt", &old_bo) << std::endl;

    // should be 1
    std::cout << "Open new.txt: "
        << open(bd, "test-bucket", "new.txt", &new_bo) << std::endl;

    // should be 1
    std::cout << "Open test.txt: " 
        << open(bd, "test-bucket", "test.txt", &old_bo) << std::endl;

    BackendObject* new_bo_1;
    // should be 1
    std::cout << "Create new1.txt: "
        << create(bd, "test-bucket", "new1.txt", &new_bo_1) << std::endl;

    BackendObject* new_bo_2;
    // should be 1
    std::cout << "Open new2.txt: "
        << open(bd, "test-bucket", "new2.txt", &new_bo_2) << std::endl;

    // should be 1
    std::cout << "Close new.txt: " << close(bd, new_bo) << std::endl;

    // should be 1
    std::cout << "Delete test.txt: " << delete_object(bd, old_bo) << std::endl;

    // should be 1
    std::cout << "Open new1.txt: "
        << open(bd, "test-bucket", "new1.txt", &new_bo_2) << std::endl;

    // should be 0, cause there are 2 references
    std::cout << "Delete new1.txt: "
        << delete_object(bd, new_bo_1) << std::endl;

    // should be 1
    std::cout << "Close new1.txt: "
        << close(bd, new_bo_1) << std::endl;

    // should be 1
    std::cout << "Delete new1.txt: " 
        << delete_object(bd, new_bo_2) << std::endl;

    fini(bd);
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
// some auxiliary functions

// create bucket
bool create_namespace(BackendData* bd, const Aws::String& bucketName) {
    Aws::S3::Model::CreateBucketRequest request;
    request.SetBucket(bucketName);

    Aws::S3::Model::CreateBucketOutcome outcome = (bd->client)->CreateBucket(request);

    if (!outcome.IsSuccess()) {
        auto err = outcome.GetError();
        std::cerr << "Error: CreateBucket: " << err.GetExceptionName() <<
            ": " << err.GetMessage() << std::endl;
    }

    return outcome.IsSuccess();
}

bool delete_bucket(BackendData* bd, const Aws::String& bucket) {
    Aws::S3::Model::DeleteBucketRequest request;
    request.SetBucket(bucket);

    Aws::S3::Model::DeleteBucketOutcome outcome = (bd->client)->DeleteBucket(request);

    if (!outcome.IsSuccess()) {
        auto err = outcome.GetError();
        std::cerr << "Error: DeleteBucket: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
        return false;
    }
    std::cout << "Successfully deleted " << bucket << std::endl;
    return true;
}

bool clean_namespace(BackendData* bd, const Aws::String&/*namespace*/ bucket) {
    BackendIterator* bi;
    get_all(bd, bucket, &bi);

    std::string name;

    while(iterate(bd, bi, name)) {
        std::cout << "deleting " << name << "..." << std::endl;
        bool ret = delete_object(bd, name, bucket);
        if (!ret) {
            return false;
        }
    }

    iterator_free(bi);

    return delete_bucket(bd, bucket);
}




