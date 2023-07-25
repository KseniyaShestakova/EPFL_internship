// MinIO C++ Library for Amazon S3 Compatible Cloud Storage
// Copyright 2022 MinIO, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "client.h"

#include <string.h>

bool bucket_exists(minio::s3::Client& client, const std::string& bucket_name) {
    minio::s3::BucketExistsArgs args;
    args.bucket = bucket_name;

    minio::s3::BucketExistsResponse resp = client.BucketExists(args);

    if (resp) {
        if (resp.exist) {
            std::cout << bucket_name << " exist" << std::endl;
            return true;
        }
        std::cout << bucket_name << " does not exist" << std::endl;
        return false;
    }
    std::cout << "unable to check bucket existence:"
                            << resp.Error().String() << std::endl;
    return true;
}


bool make_bucket(minio::s3::Client& client,
                 const std::string& bucket_name) {
    if (bucket_exists(client, bucket_name)) {
        std::cout << bucket_name << " already exists, skipping!" << std::endl;
        return false;
    }
    minio::s3::MakeBucketArgs args;
    args.bucket = bucket_name;

    minio::s3::MakeBucketResponse resp = client.MakeBucket(args);

    if (resp) {
        std::cout << bucket_name << " was created" << std::endl;
        return true;
    } 
    std::cout << "unable to create " << bucket_name << 
        resp.Error().String() << std::endl;
    return false;
}

bool stat_object(minio::s3::Client& client,
                 const std::string& bucket_name,
                 const std::string& object_name) {
    minio::s3::StatObjectArgs args;
    args.bucket = bucket_name;
    args.object = object_name;

    minio::s3::StatObjectResponse resp = client.StatObject(args);

    if (resp) {
        std::cout << "Version ID: " << resp.version_id << std::endl;
        std::cout << "ETag: " << resp.etag << std::endl;
        std::cout << "Size: " << resp.size << std::endl;
        std::cout << "Last Modified: " << resp.last_modified << std::endl;
        std::cout << "Retention Mode: ";
        if (minio::s3::IsRetentionModeValid(resp.retention_mode)) {
            std::cout << minio::s3::RetentionModeToString(resp.retention_mode)
                                                                << std::endl;
        } else {
            std::cout << "-" << std::endl;
        }
        std::cout << "Retention Retain Until Date: ";
        if (resp.retention_retain_until_date) {
          std::cout << resp.retention_retain_until_date.ToHttpHeaderValue()
                    << std::endl;
        } else {
          std::cout << "-" << std::endl;
        }
        std::cout << "Legal Hold: ";
        if (minio::s3::IsLegalHoldValid(resp.legal_hold)) {
          std::cout << minio::s3::LegalHoldToString(resp.legal_hold) << std::endl;
        } else {
          std::cout << "-" << std::endl;
        }
        std::cout << "Delete Marker: "
                  << minio::utils::BoolToString(resp.delete_marker) << std::endl;
        std::cout << "User Metadata: " << std::endl;
        std::list<std::string> keys = resp.user_metadata.Keys();
        for (auto& key : keys) {
          std::cout << "  " << key << ": " << resp.user_metadata.GetFront(key)
                    << std::endl;
        }

        return true;
    }
    std::cout << "unable to get stat: " << resp.Error().String() << std::endl;
    return false;
}

bool upload_object(minio::s3::Client& client,
                   const std::string& bucket_name,
                   const std::string& object_name,
                   const std::string& filename) {
    if (!bucket_exists(client, bucket_name)) {
        std::cout << bucket_name << " does not exist, scipping!" << std::endl;
        return false;
    }

    minio::s3::UploadObjectArgs args;
    args.bucket = bucket_name;
    args.object = object_name;
    args.filename = filename;

    minio::s3::UploadObjectResponse resp = client.UploadObject(args);

    if (resp) {
        std::cout << object_name << " successfully uploaded to " << 
                     bucket_name << std::endl;
        return true;
    }
    std::cout << "unable to upload object: " << resp.Error().String() << std::endl;
    return false;
}

void show_object(minio::s3::Client& client,
                 const std::string& bucket_name,
                 const std::string& object_name) {
    minio::s3::GetObjectArgs args;
    args.bucket = bucket_name;
    args.object = object_name;
    // could capture link to buffer
    // and size of already read bytes? and do read that way
    std::cout << "content of " << object_name << ": ";
    args.datafunc = [](minio::http::DataFunctionArgs args) -> bool {
        std::cout << args.datachunk;
        return true;
    };

    minio::s3::GetObjectResponse resp = client.GetObject(args);
    if (!resp) {
        std::cout << "unable to get object: " << resp.Error().String();
    }
    std::cout << std::endl;
}

//TODO: only empty bucket can be removed, so cleaning up should be done previously
bool remove_bucket(minio::s3::Client& client,
                   const std::string& bucket_name) {
    if (!bucket_exists(client, bucket_name)) {
        std::cout << bucket_name << " does not exist, scipping!" << std::endl;
        return false;
    }

    minio::s3::RemoveBucketArgs args;
    args.bucket = bucket_name;

    minio::s3::RemoveBucketResponse resp = client.RemoveBucket(args);

    if (resp) {
        std::cout << bucket_name << " was successfully deleted" << std::endl;
        return true;
    }
    std::cout << "unable to remove bucket: " << resp.Error().String() << std::endl;
    return false;
}

bool remove_object(minio::s3::Client& client,
                   const std::string& bucket_name,
                   const std::string& object_name) {
    minio::s3::RemoveObjectArgs args;
    args.bucket = bucket_name;
    args.object = object_name;

    minio::s3::RemoveObjectResponse resp = client.RemoveObject(args);

    if (resp) {
        std::cout << object_name << " is removed successfully" << std::endl;
        return true;
    }
    std::cout << "unable to remove object; " << resp.Error().String()
              << std::endl;
    return false;
}

void remove_objects_example(minio::s3::Client& client,
                            const std::string&  bucket_name) {
    // first prepare objects
    upload_object(client, bucket_name, "object-1", "/home/xxeniash/test.txt");
    upload_object(client, bucket_name, "object-2", "/home/xxeniash/test.txt");
    upload_object(client, bucket_name, "object-3", "/home/xxeniash/test.txt");

    minio::s3::RemoveObjectsArgs args;
    args.bucket = bucket_name;

    std::list<minio::s3::DeleteObject> objects;
    objects.push_back(minio::s3::DeleteObject{"object-1"});
    objects.push_back(minio::s3::DeleteObject{"object-2"});
    objects.push_back(minio::s3::DeleteObject{"object-3"});

    std::list<minio::s3::DeleteObject>::iterator it = objects.begin();

    args.func = [&objects = objects, &it = it](minio::s3::DeleteObject& object) -> bool {
        if (it == objects.end()) return false;
        object = *it;
        ++it;
        return true;
    };

    minio::s3::RemoveObjectsResult result = client.RemoveObjects(args);
    for (; result; result++) {
        minio::s3::DeleteError err = *result;
        if (!err) {
            std::cout << "unable to do remove objects; " << err.Error().String()
                << std::endl;
            break;
        }

        std::cout << "unable to remove object " << err.object_name  << std::endl;
    }
}

void list_example(minio::s3::Client& client, 
                  const std::string& bucket_name,
                  const std::string& prefix,
                  const std::string& marker) {
    // first prepare objects
    upload_object(client, bucket_name, "object-1", "/home/xxeniash/test.txt");
    upload_object(client, bucket_name, "object-2", "/home/xxeniash/test.txt");
    upload_object(client, bucket_name, "object-3", "/home/xxeniash/test.txt");

    // somehow all this arguments change nothing((
    minio::s3::ListObjectsArgs args;
    args.bucket = bucket_name;
    args.prefix = prefix;
    args.start_after = marker;
    args.max_keys = 1;

    std::cout << "trying to list " << bucket_name << std::endl;
    std::cout << "with prefix: " << prefix << std::endl;
    std::cout << "with marker: " << marker << std::endl;

    minio::s3::ListObjectsResult result = client.ListObjects(args);
    for (; result; result++) {
        minio::s3::Item item = *result;
        if (item) {
            std::cout << item.name << std::endl;
        } else {
            std::cout << "unable to list objects: " << item.Error().String() << std::endl;
            break;
        }
    }
}


int main(int argc, char* argv[]) {
	// set-up: create S3 base URL
    minio::s3::BaseUrl base_url("play.min.io");

    // create credential provider
    // probably accepts arbitrary credentials
    minio::creds::StaticProvider provider("minioadmin", "minioadmin");

    // create S3 client - based on URL and provider
    minio::s3::Client client(base_url, &provider);

    // let's start with creating bucket
    make_bucket(client, "test-bucket");
    upload_object(client, "test-bucket", "test-object", "/home/xxeniash/test.txt");
    stat_object(client, "test-bucket", "test-object");
    show_object(client, "test-bucket", "test-object");
    //remove_object(client, "test-bucket", "test-object");
    //remove_bucket(client, "test-bucket");
    remove_objects_example(client, "test-bucket");
    list_example(client, "test-bucket", "obj", "object-2");

    return 0;

}
