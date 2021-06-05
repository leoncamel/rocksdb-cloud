
#include <jni.h>

#include "include/org_rocksdb_CloudEnv.h"
#include "rocksdb/cloud/db_cloud.h"
#include "rocksdb/cloud/cloud_env_options.h"
#include "rocksdb/options.h"
#include "rocksjni/portal.h"

/*
 * Class:     org_rocksdb_CloudEnv
 * Method:    createCloudEnv
 * Signature: (J)J
 */
jlong JNICALL Java_org_rocksdb_CloudEnv_createCloudEnv
  (JNIEnv* env, jclass, jlong jhandle_cloud_env_options) {

  auto *ceo = reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions *>(jhandle_cloud_env_options);

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
