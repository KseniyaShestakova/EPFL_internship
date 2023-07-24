# Amazon S3
Amazon Simple Storage Serviceis an object storage service. \
[User guide](https://docs.aws.amazon.com/AmazonS3/latest/userguide/Welcome.html) \
[SDKs](https://aws.amazon.com/developer/tools/) \
[AWS free tier](http://aws.amazon.com/free). Free account can be created here. \
[C++ examples](https://github.com/awsdocs/aws-doc-sdk-examples/tree/main/cpp/example_code/s3) \
[Short version of documentation](https://docs.aws.amazon.com/AmazonS3/latest/API/API_Operations_Amazon_Simple_Storage_Service.html) \
[SDK documentation](https://sdk.amazonaws.com/cpp/api/LATEST/root/html/index.html) \
Offers different storage classes depending on how often are you using your storage,
from which regions are doing that and so on. \
There are different tools for storage management for managing costs, meeting regulatory requirements,
reducing latency and data replication. 
Examples: S3 Lifecycle (configure lifecycle), S3 Object Look (prevent objects from being deleted of overwritten),
S3 Replication (replicate objects), S3 Batch Operations (apply same operation to multiple objects simultaneously). \

Amazon S3 supports access management and security via S3 Block Public Access, AWS Identity and Access Management,
Bucket policies, Amazon S3 access points, Access control lists, S3 Object Ownership. 

There are tools for transforming data and triggering workflows: 
S3 Object Lambda (add triggers for GET, HEAD, LIST), 
Event notifications (trigger workflows that use Amazon SNS and Amzon SQS)

Amazon also provides tools for logging and monitoring, both automated and manual.

Amazon provides tools for analyzing storage usage in order to get better understanding and 
optimize storage usage.

Has it's own **data consistency model**. Has strong read-after-write consistency for PUT and DELETE requests.
Some examples of concurrent applications behavior can be found in the user guide.

There are several related services. Data loaded into Amazon can be later used with these services. 

**Accessing Amazon S3:**
* *AWS managing console* is a web-based interface for managing Amazon S3 and AWS resources.
  If you signed up for an AWS account, you can access the Amazon S3 console by signing int the
  AWS Manaagement Console and choosing **S3** from the AWS Management Console home page
* *AWS Command Line Interface* is supported on Windows, macOS, Linux.
* *AWS SDKs (software development kits)* consist of libraries and sample code for various
  programming languages and platforms (Java, Python, iOS, Android, etc.).
  The requests wrap underlying REST API.
* *Amazon S3 REST API* is an HTTP interface to Amazon S3. Can be used with any toolkit supporting HTTP.
  AWS SDKs wrap this API adding signature computing, cryptographically signing requests,
  managing errors and retrying requests automatically.

## How it works
This storage is a flat one, with *objects* (files with metadata describing it) 
stored inside *buckets* (containers with specified name and AWS region).

**Main entities:**
* *Bucket* - a container for objects. Has name and AWS region, which cannot be changed after creation.
  Name is an unique identifier and should follow certain [rules](https://docs.aws.amazon.com/AmazonS3/latest/userguide/bucketnamingrules.html).
*  *Objects* consist of object data and metadata
  (include default ones, like date last modified, and HTTP metadata).
  Object is uniquely identified within a bucket with [key](https://docs.aws.amazon.com/AmazonS3/latest/userguide/Welcome.html#BasicsKeys)
  and [version ID](https://docs.aws.amazon.com/AmazonS3/latest/userguide/Welcome.html#BasicsVersionID).
  More info about [keys](https://docs.aws.amazon.com/AmazonS3/latest/userguide/object-keys.html) and
  [versioning](https://docs.aws.amazon.com/AmazonS3/latest/userguide/Versioning.html).
* *Bucket Policy* is a resource-based AWS identity to grant access permissions to your bucket and objects in it.
   Only the bucket owner can associate a policy with a bucket.
   Permissions attached to bucket are applied to all the objects inside a bucket.
* *S3 Access points* are named network endpoints with dedicated access policies that describe how
  data canbe accessed using that endpoint.
* *Access control lists (ACLs)* are used for granting read and write permissions to authorized users.
  It is not recommended to use ACLs except unusual circumstances where you need to control access
  to each object individually.
* *Regions*. You can choose geographical AWS Region where Amazon S3 stores the buckets that you create
  in order to optimize latency, minimize cost or address regulatory requirements.

  ## MinIO
  MinIO is an object storage solution that provides an Amazon Web Services S3-compatible API and supports core
  S3 features.
  So the **idea** of developing with Amazon tools is the next:
  try free tier of the Amazon S3 for writing a small app,
  write JULEA backend using Amazon API,
  test and benchmark it using MinIO server.
  
  Installation guides:
  [docker](https://min.io/docs/minio/container/index.html),
  [linux](https://min.io/docs/minio/linux/index.html).


  
  
