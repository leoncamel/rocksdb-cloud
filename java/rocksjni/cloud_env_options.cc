
#include <jni.h>
#include <iostream>

#include "include/org_rocksdb_CloudEnvOptions.h"
#include "rocksdb/cloud/cloud_env_options.h"
#include "rocksjni/jnipp.h"

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

/*
 * Class:     org_rocksdb_CloudEnvOptions
 * Method:    setSrcBucketOptions
 * Signature: (JLorg/rocksdb/BucketOptions;)V
 */
void JNICALL Java_org_rocksdb_CloudEnvOptions_setSrcBucketOptions
  (JNIEnv* env, jclass, jlong jhandle, jobject bucketOptions) {

  jni::init(env);

	auto *options =
    reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions*>(jhandle);
  if (options == nullptr) {
    // exception thrown: OutOfMemoryError
    return;
  }

  jni::Object bo(bucketOptions);

  std::string bucket = bo.get<std::string>("bucket");
  std::string prefix = bo.get<std::string>("prefix");
  std::string object_path = bo.get<std::string>("object");
  std::string region = bo.get<std::string>("region");

#if 0
  std::cout << "SrcBucketOptions: \n"
    << "bucket: " << bucket << "\n"
    << "prefix: " << prefix << "\n"
    << "object: " << object_path << "\n"
    << "region: " << region << "\n";
#endif

  options->src_bucket.SetBucketName(bucket, prefix);
  options->src_bucket.SetObjectPath(object_path);
  options->src_bucket.SetRegion(region);
}

/*
 * Class:     org_rocksdb_CloudEnvOptions
 * Method:    getSrcBucketOptions
 * Signature: (J)Lorg/rocksdb/BucketOptions;
 */
JNIEXPORT jobject JNICALL Java_org_rocksdb_CloudEnvOptions_getSrcBucketOptions
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_rocksdb_CloudEnvOptions
 * Method:    setDestBucketOptions
 * Signature: (JLorg/rocksdb/BucketOptions;)V
 */
void JNICALL Java_org_rocksdb_CloudEnvOptions_setDestBucketOptions
  (JNIEnv* env, jclass, jlong jhandle, jobject bucketOptions) {

  jni::init(env);

	auto *options =
    reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions*>(jhandle);
  if (options == nullptr) {
    // exception thrown: OutOfMemoryError
    return;
  }

  jni::Object bo(bucketOptions);

  std::string bucket = bo.get<std::string>("bucket");
  std::string prefix = bo.get<std::string>("prefix");
  std::string object_path = bo.get<std::string>("object");
  std::string region = bo.get<std::string>("region");

#if 0
  std::cout << "DestBucketOptions: \n"
    << "bucket: " << bucket << "\n"
    << "prefix: " << prefix << "\n"
    << "object: " << object_path << "\n"
    << "region: " << region << "\n";
#endif

  options->dest_bucket.SetBucketName(bucket, prefix);
  options->dest_bucket.SetObjectPath(object_path);
  options->dest_bucket.SetRegion(region);
}

/*
 * Class:     org_rocksdb_CloudEnvOptions
 * Method:    getDestBucketOptions
 * Signature: (J)Lorg/rocksdb/BucketOptions;
 */
JNIEXPORT jobject JNICALL Java_org_rocksdb_CloudEnvOptions_getDestBucketOptions
  (JNIEnv *, jclass, jlong);
