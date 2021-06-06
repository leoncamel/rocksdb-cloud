
#include <jni.h>
#include <cstdio>
#include <iostream>

#include "include/org_rocksdb_CloudEnv.h"
#include "rocksdb/cloud/db_cloud.h"
#include "rocksdb/cloud/cloud_env_options.h"
#include "rocksdb/options.h"
#include "rocksjni/portal.h"


void show_CloudEnvOptions(ROCKSDB_NAMESPACE::CloudEnvOptions* ceo) {
  std::cout << "========== CloudEnvOptions ==========" << std::endl;
  std::cout << "s3 override : " << ceo->endpointOverride << std::endl;

  std::cout << "bucket_name : " << ceo->src_bucket.GetBucketName() << std::endl;
  std::cout << "object_path : " << ceo->src_bucket.GetObjectPath() << std::endl;
  std::cout << "region      : " << ceo->src_bucket.GetRegion() << std::endl;

  std::cout << "bucket_name : " << ceo->dest_bucket.GetBucketName() << std::endl;
  std::cout << "object_path : " << ceo->dest_bucket.GetObjectPath() << std::endl;
  std::cout << "region      : " << ceo->dest_bucket.GetRegion() << std::endl;
}

/*
 * Class:     org_rocksdb_CloudEnv
 * Method:    createCloudEnv
 * Signature: (J)J
 */
jlong JNICALL Java_org_rocksdb_CloudEnv_createCloudEnv
  (JNIEnv* env, jclass, jlong jhandle_cloud_env_options) {

  auto *ceo = reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions *>(jhandle_cloud_env_options);

#if 0
  show_CloudEnvOptions(ceo);
#endif

  ROCKSDB_NAMESPACE::CloudEnv* cenv;
  ROCKSDB_NAMESPACE::Status s =
    ROCKSDB_NAMESPACE::CloudEnv::NewAwsEnv(ROCKSDB_NAMESPACE::Env::Default(), *ceo, nullptr, &cenv);

  if (!s.ok()) {
    // TODO: add logging
    // fprintf(stderr, "Unable to create cloud env in bucket %s. %s\n",
    //         bucketName.c_str(), s.ToString().c_str());

    ROCKSDB_NAMESPACE::RocksDBExceptionJni::ThrowNew(env, s);
    return 0;
  }

  return reinterpret_cast<jlong>(cenv);
}

/*
 * Class:     org_rocksdb_CloudEnv
 * Method:    disposeInternal
 * Signature: (J)V
 */
void JNICALL Java_org_rocksdb_CloudEnv_disposeInternal
  (JNIEnv *, jobject, jlong jhandle) {
  auto *eo = reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnv *>(jhandle);
  assert(eo != nullptr);
  delete eo;
}
