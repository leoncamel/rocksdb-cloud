
#include <jni.h>

#include "include/org_rocksdb_CloudEnvOptions.h"
#include "rocksdb/cloud/db_cloud.h"
#include "rocksdb/options.h"

/*
 * Class:     org_rocksdb_CloudEnv
 * Method:    createCloudEnv
 * Signature: (J)J
 */
jlong JNICALL Java_org_rocksdb_CloudEnv_createCloudEnv
  (JNIEnv* env, jclass, jlong jhandle_cloud_env_options) {

  auto *ceo = reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions *>(jhandle_cloud_env_options);

  CloudEnv* cenv;
  Status s = CloudEnv::NewAwsEnv(Env::Default(), ceo, nullptr, &cenv);
  if (!s.ok()) {
    fprintf(stderr, "Unable to create cloud env in bucket %s. %s\n",
            bucketName.c_str(), s.ToString().c_str());

    // TODO: Throw exception
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
  (JNIEnv *, jobject, jlong) {
  auto *eo = reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions *>(jhandle);
  assert(eo != nullptr);
  delete eo;
}
