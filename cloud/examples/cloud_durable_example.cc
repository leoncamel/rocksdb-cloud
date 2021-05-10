// Copyright (c) 2017-present, Rockset, Inc.  All rights reserved.
#include <cstdio>
#include <iostream>
#include <string>

#include "rocksdb/cloud/db_cloud.h"
#include "rocksdb/options.h"

using namespace ROCKSDB_NAMESPACE;

// This is the local directory where the db is stored.
std::string kDBPath = "/tmp/rocksdb_cloud_durable";

// This is the name of the cloud storage bucket where the db
// is made durable. if you are using AWS, you have to manually
// ensure that this bucket name is unique to you and does not
// conflict with any other S3 users who might have already created
// this bucket name.
std::string kBucketSuffix = "cloud.durable.example.";
std::string kRegion = "us-west-2";

static const bool flushAtEnd = true;
static const bool disableWAL = false;

int main() {
  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // cloud environment config options here
  CloudEnvOptions cloud_env_options;
  cloud_env_options.endpointOverride = "http://127.0.0.1:9000";

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // Store a reference to a cloud env. A new cloud env object should be
  // associated
  // with every new cloud-db.
  std::unique_ptr<CloudEnv> cloud_env;

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  if (!cloud_env_options.credentials.HasValid().ok()) {
    fprintf(
        stderr,
        "Please set env variables "
        "AWS_ACCESS_KEY_ID and AWS_SECRET_ACCESS_KEY with cloud credentials");
    return -1;
  }

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // Append the user name to the bucket name in an attempt to make it
  // globally unique. S3 bucket-names need to be globally unique.
  // If you want to rerun this example, then unique user-name suffix here.
  char* user = getenv("USER");
  kBucketSuffix.append(user);

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // "rockset." is the default bucket prefix
  const std::string bucketPrefix = "rockset.";
  cloud_env_options.src_bucket.SetBucketName(kBucketSuffix, bucketPrefix);
  cloud_env_options.dest_bucket.SetBucketName(kBucketSuffix, bucketPrefix);

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // create a bucket name for debugging purposes
  const std::string bucketName = bucketPrefix + kBucketSuffix;

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // Create a new AWS cloud env Status
  CloudEnv* cenv;
  Status s = CloudEnv::NewAwsEnv(Env::Default(), kBucketSuffix, kDBPath,
                                 kRegion, kBucketSuffix, kDBPath, kRegion,
                                 cloud_env_options, nullptr, &cenv);
  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  if (!s.ok()) {
    fprintf(stderr, "Unable to create cloud env in bucket %s. %s\n",
            bucketName.c_str(), s.ToString().c_str());
    return -1;
  }
  cloud_env.reset(cenv);

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // Create options and use the AWS env that we created earlier
  Options options;
  options.env = cloud_env.get();
  options.create_if_missing = true;

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // No persistent read-cache
  std::string persistent_cache = "";

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // options for each write
  WriteOptions wopt;
  wopt.disableWAL = disableWAL;

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // open DB
  DBCloud* db;
  s = DBCloud::Open(options, kDBPath, persistent_cache, 0, &db);
  if (!s.ok()) {
    fprintf(stderr, "Unable to open db at path %s with bucket %s. %s\n",
            kDBPath.c_str(), bucketName.c_str(), s.ToString().c_str());
    return -1;
  }

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // Put key-value
  s = db->Put(wopt, "key1", "value");
  assert(s.ok());
  std::string value;
  // get value
  s = db->Get(ReadOptions(), "key1", &value);
  assert(s.ok());
  assert(value == "value");

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // atomically apply a set of updates
  {
    WriteBatch batch;
    batch.Delete("key1");
    batch.Put("key2", value);
    s = db->Write(wopt, &batch);
  }

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  s = db->Get(ReadOptions(), "key1", &value);
  assert(s.IsNotFound());

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  db->Get(ReadOptions(), "key2", &value);
  assert(value == "value");

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // print all values in the database
  ROCKSDB_NAMESPACE::Iterator* it =
      db->NewIterator(ROCKSDB_NAMESPACE::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    std::cout << it->key().ToString() << ": " << it->value().ToString()
              << std::endl;
  }
  delete it;

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  // Flush all data from main db to sst files. Release db.
  if (flushAtEnd) {
    db->Flush(FlushOptions());
  }
  delete db;

  fprintf(stdout, "%s at line %d\n", __FUNCTION__, __LINE__);
  fprintf(stdout, "Successfully used db at path %s in bucket %s.\n",
          kDBPath.c_str(), bucketName.c_str());
  return 0;
}
