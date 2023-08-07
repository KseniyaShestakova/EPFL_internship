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

bool put_object(const Aws::String& bucket_name,
                const Aws::String& file_name,
                const Aws::S3::S3Client& s3_client) {
    Aws::S3::Model::PutObjectRequest request;
    request.SetBucket(bucket_name);
    request.SetKey(file_name);

    std::shared_ptr<Aws::IOStream> inputData =
        Aws::MakeShared<Aws::FStream>("SampleAllocationTag",
                                      file_name.c_str(),
                                      std::ios_base::in | std::ios_base::binary);
    if (!*inputData) {
        std::cerr << "Error unable to read file " << file_name << std::endl;
        return false;
    }

    request.SetBody(inputData);

    Aws::S3::Model::PutObjectOutcome outcome = s3_client.PutObject(request);

    if (!outcome.IsSuccess()) {
        std::cerr << "Error: PutObject: " <<
            outcome.GetError().GetMessage() << std::endl;
    } else {
        std::cout << "Added object " << file_name << " to bucket " <<
            bucket_name << std::endl;
    }

    return outcome.IsSuccess();
}

bool list_buckets(const Aws::S3::S3Client& client) {
    auto outcome = client.ListBuckets();

    bool result = true;
    if (!outcome.IsSuccess()) {
        std::cerr << "ListBuckets Error: " << outcome.GetError() << std::endl;
        result = false;
    } else {
        std::cout << "Found " << outcome.GetResult().GetBuckets().size() << " buckets\n";
        for (auto&& b: outcome.GetResult().GetBuckets()) {
            std::cout << b.GetName() << std::endl;
        }
    }

    return result;
}

bool create_bucket(const Aws::String& bucket_name,
                   const Aws::S3::S3Client& client) {
    Aws::S3::Model::CreateBucketRequest request;
    request.SetBucket(bucket_name);

    Aws::S3::Model::CreateBucketOutcome outcome = client.CreateBucket(request);
    if (!outcome.IsSuccess()) {
        auto err = outcome.GetError();
        std::cerr << "Error: CreateBucket: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
    } else {
        std::cout << "Created bucket " << bucket_name << std::endl;
    }

    return outcome.IsSuccess();
}

bool delete_bucket(const Aws::String& bucket_name,
                   const Aws::S3::S3Client& client) {
    Aws::S3::Model::DeleteBucketRequest request;
    request.SetBucket(bucket_name);

    Aws::S3::Model::DeleteBucketOutcome outcome = client.DeleteBucket(request);

    if (!outcome.IsSuccess()) {
        auto err = outcome.GetError();
        std::cerr << "Error: DeleteBucket: " << 
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
    } else {
        std::cout << "Bucket " << bucket_name << " was deleted" << std::endl;
    }

    return outcome.IsSuccess();
}

bool list_objects(const Aws::String& bucket_name,
                  const Aws::S3::S3Client& client,
                  const Aws::String& prefix = "") {
    Aws::S3::Model::ListObjectsRequest request;
    request.WithBucket(bucket_name);
    request.WithPrefix(prefix);

    auto outcome = client.ListObjects(request);

    std::cout << "\nList of objects in " << bucket_name << ":" << std::endl;

    if (!outcome.IsSuccess()) {
        std::cerr << "Error: ListObjects: " << 
            outcome.GetError().GetMessage() << std::endl;
    } else {
        Aws::Vector<Aws::S3::Model::Object> objects = outcome.GetResult().GetContents();

        for (Aws::S3::Model::Object& object: objects) {
            std::cout << object.GetKey() << std::endl;
        }
    }

    return outcome.IsSuccess();
}

bool read_object(const Aws::String& /*object name*/object_key,
                const Aws::String& bucket_name,
                const Aws::S3::S3Client& client) {
    Aws::S3::Model::GetObjectRequest request;
    request.SetBucket(bucket_name);
    request.SetKey(object_key);
    request.SetRange("bytes=3-10");

    Aws::S3::Model::GetObjectOutcome outcome = client.GetObject(request);
    if (!outcome.IsSuccess()) {
        auto err = outcome.GetError();
        std::cerr << "Error: GetObject: " <<
            err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
    } else {
        std::cout << "Retrieved " << object_key << std::endl;
    }

    Aws::S3::Model::GetObjectResult& result = outcome.GetResult();

    unsigned int cnt = 0;
    unsigned int total = result.GetContentLength();
    std::string str;

    std::cout << "Content length: " << total << std::endl;

    while (cnt < total) {
        result.GetBody() >> str;
        std::cout << str << " ";
        cnt += str.size() + 1;
    }

    std::cout << std::endl;

    return outcome.IsSuccess();
}

int main()
{
    Aws::SDKOptions options;
    Aws::InitAPI(options);

    const Aws::String bucket_name = "test-bucket";
    const Aws::String object_name = "test1.txt";

    Aws::Client::ClientConfiguration cfg;
    cfg.endpointOverride = "127.0.0.1:9000";
    cfg.scheme = Aws::Http::Scheme::HTTP;
    cfg.verifySSL = false;

    Aws::S3::S3Client s3_client(Aws::Auth::AWSCredentials("minioadmin", "minioadmin"),
                       cfg,
                       Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never,
                       false);


    delete_bucket("new-bucket", s3_client);
    //put_object(bucket_name, object_name, s3_client);
    list_buckets(s3_client);
    list_objects("test-bucket", s3_client);
    
    read_object("test.txt", "test-bucket", s3_client);

    Aws::ShutdownAPI(options);

    return 0;
}

