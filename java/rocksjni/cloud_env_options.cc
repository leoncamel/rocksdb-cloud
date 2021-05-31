
#include <jni.h>

#include "include/org_rocksdb_CloudEnvOptions.h"
#include "rocksdb/cloud/cloud_env_options.h"


/*
 * Class:     org_rocksdb_CloudEnvOptions
 * Method:    newCloudEnvOptions
 * Signature: ()J
 */
jlong JNICALL Java_org_rocksdb_CloudEnvOptions_newCloudEnvOptions
  (JNIEnv *, jclass) {
  auto *cloud_env_opt = new ROCKSDB_NAMESPACE::CloudEnvOptions();
  return reinterpret_cast<jlong>(cloud_env_opt);
}

/*
 * Class:     org_rocksdb_CloudEnvOptions
 * Method:    disposeInternal
 * Signature: (J)V
 */
void JNICALL Java_org_rocksdb_CloudEnvOptions_disposeInternal
  (JNIEnv *, jobject, jlong jhandle) {
  auto *eo = reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions *>(jhandle);
  assert(eo != nullptr);
  delete eo;
}


/*
 * Class:     org_rocksdb_CloudEnvOptions
 * Method:    setEndpointOverride
 * Signature: (JLjava/lang/String;)J
 */
void JNICALL Java_org_rocksdb_CloudEnvOptions_setEndpointOverride
  (JNIEnv* env, jclass, jlong jhandle, jstring endpoint) {
  auto *options =
    reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions*>(jhandle);
  const char* ep = env->GetStringUTFChars(endpoint, nullptr);
  if (ep == nullptr) {
    // exception thrown: OutOfMemoryError
    return;
  }

  options->endpointOverride = ep;
}

/*
 * Class:     org_rocksdb_CloudEnvOptions
 * Method:    getEndpointOverride
 * Signature: (J)Ljava/lang/String;
 */
jstring JNICALL Java_org_rocksdb_CloudEnvOptions_getEndpointOverride
  (JNIEnv* env, jclass, jlong jhandle) {
  auto *options =
    reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions*>(jhandle);
  if (options == nullptr) {
    // exception thrown: OutOfMemoryError
    return nullptr;
  }

  return env->NewStringUTF(options->endpointOverride.c_str());
}
