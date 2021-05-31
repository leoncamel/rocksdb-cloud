
#include <jni.h>

#include "include/org_rocksdb_CloudEnvOptions.h"
#include "rocksdb/cloud/cloud_env_options.h"


/*
 * Class:     org_rocksdb_CloudEnvOptions
 * Method:    newCloudEnvOptions
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_rocksdb_CloudEnvOptions_newCloudEnvOptions
  (JNIEnv *, jclass) {
  auto *cloud_env_opt = new ROCKSDB_NAMESPACE::CloudEnvOptions();
  return reinterpret_cast<jlong>(cloud_env_opt);
}

/*
 * Class:     org_rocksdb_CloudEnvOptions
 * Method:    disposeInternal
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_rocksdb_CloudEnvOptions_disposeInternal
  (JNIEnv *, jobject, jlong jhandle) {
  auto *eo = reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions *>(jhandle);
  assert(eo != nullptr);
  delete eo;
}

