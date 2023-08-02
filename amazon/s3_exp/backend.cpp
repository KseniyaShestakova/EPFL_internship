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

struct BackendData {
    std::string path = "127.0.0.1:9000";
    Aws::SDKOptions* options;
    Aws::S3::S3Client* client;
};

struct BackendObject {
    Aws::String bucket;
    Aws::String objectKey;

};

bool open(BackendData* bd, const Aws::String&/*namespace*/ bucket,
                           const Aws::String&/*path*/ object,
                           BackendObject** bo) {
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
    } else {
        std::cout << "Added object " << object << " to bucket " <<
            bucket << std::endl;
        *bo = new BackendObject;
        (*bo)->bucket = bucket;
        (*bo)->objectKey = object;
    }
    return outcome.IsSuccess();
}

bool delete_object(BackendData* bd, BackendObject* bo) {
    Aws::S3::Model::DeleteObjectRequest request;

    request.SetBucket(bo->bucket);
    request.SetKey(bo->objectKey);

    Aws::S3::Model::DeleteObjectOutcome outcome = (bd->client)->DeleteObject(request);

    if (!outcome.IsSuccess()) {
        auto err = outcome.GetError();
        std::cerr << "Error: DeleteObject: " <<
                  err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
    } else {
        std::cout << "Successfully deleted " << bo->objectKey << std::endl;
    }

    return outcome.IsSuccess();
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
    Aws::ShutdownAPI(*(bd->options));

    delete bd->options;
    delete bd->client;

    delete bd;
}

int main() {
    std::string path = "127.0.0.1:9000";
    BackendData* bd = nullptr;
    init(path, &bd);

    BackendObject* bo = nullptr;
    open(bd, "test-bucket", "new.txt", &bo); 

    delete_object(bd, bo);

    fini(bd);
}




