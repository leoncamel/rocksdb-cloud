
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

/*
 * Class:     org_rocksdb_CloudEnvOptions
 * Method:    setSrcBucketOptions
 * Signature: (JLorg/rocksdb/BucketOptions;)V
 */
void JNICALL Java_org_rocksdb_CloudEnvOptions_setSrcBucketOptions
  (JNIEnv* env, jclass, jlong jhandle, jobject bucketOptions) {

	auto *options =
    reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions*>(jhandle);
  if (options == nullptr) {
    // exception thrown: OutOfMemoryError
    return;
  }


  jclass cls = env->GetObjectClass(bucketOptions);

  /*
   * Get src_bucket.bucket_
   */
  jfieldID fid_bucket = env->GetFieldID(cls, "bucket_", "Ljava/lang/String;");
  jstring s_val_bucket = (jstring) env->GetObjectField(bucketOptions, fid_bucket);

  // we have to get string bytes into C string
  const char *c_str_bucket;
  c_str_bucket = env->GetStringUTFChars (s_val_bucket, NULL);
  if (c_str_bucket == NULL) {
    return;
  }
  std::string bucket = c_str_bucket;

  // after using it, remember to release the memory
  env->ReleaseStringUTFChars (s_val_bucket, c_str_bucket);

  /*
   * Get src_bucket.prefix_
   */
  // TODO: refactor this duplicated code
  jfieldID fid_prefix = env->GetFieldID(cls, "prefix_", "Ljava/lang/String;");
  jstring s_val_prefix = (jstring) env->GetObjectField(bucketOptions, fid_prefix);

  // we have to get string bytes into C string
  const char *c_str_prefix;
  c_str_prefix = env->GetStringUTFChars (s_val_prefix, NULL);
  if (c_str_prefix == NULL) {
    return;
  }
  std::string prefix = c_str_prefix;

  // after using it, remember to release the memory
  env->ReleaseStringUTFChars (s_val_prefix, c_str_prefix);

  /*
   * Get src_bucket.object_
   */
  // TODO: refactor this duplicated code
  jfieldID fid_object = env->GetFieldID(cls, "object_", "Ljava/lang/String;");
  jstring s_val_object = (jstring) env->GetObjectField(bucketOptions, fid_object);

  // we have to get string bytes into C string
  const char *c_str_object;
  c_str_object = env->GetStringUTFChars (s_val_object, NULL);
  if (c_str_object == NULL) {
    return;
  }
  std::string object_path = c_str_object;

  // after using it, remember to release the memory
  env->ReleaseStringUTFChars (s_val_object, c_str_object);

  /*
   * Get src_bucket.region_
   */
  // TODO: refactor this duplicated code
  jfieldID fid_region = env->GetFieldID(cls, "region_", "Ljava/lang/String;");
  jstring s_val_region = (jstring) env->GetObjectField(bucketOptions, fid_region);

  // we have to get string bytes into C string
  const char *c_str_region;
  c_str_region = env->GetStringUTFChars (s_val_region, NULL);
  if (c_str_region == NULL) {
    return;
  }
  std::string region = c_str_region;

  // after using it, remember to release the memory
  env->ReleaseStringUTFChars (s_val_region, c_str_region);

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

	auto *options =
    reinterpret_cast<ROCKSDB_NAMESPACE::CloudEnvOptions*>(jhandle);
  if (options == nullptr) {
    // exception thrown: OutOfMemoryError
    return;
  }


  jclass cls = env->GetObjectClass(bucketOptions);

  /*
   * Get dest_bucket.bucket_
   */
  jfieldID fid_bucket = env->GetFieldID(cls, "bucket_", "Ljava/lang/String;");
  jstring s_val_bucket = (jstring) env->GetObjectField(bucketOptions, fid_bucket);

  // we have to get string bytes into C string
  const char *c_str_bucket;
  c_str_bucket = env->GetStringUTFChars (s_val_bucket, NULL);
  if (c_str_bucket == NULL) {
    return;
  }
  std::string bucket = c_str_bucket;

  // after using it, remember to release the memory
  env->ReleaseStringUTFChars (s_val_bucket, c_str_bucket);

  /*
   * Get dest_bucket.prefix_
   */
  // TODO: refactor this duplicated code
  jfieldID fid_prefix = env->GetFieldID(cls, "prefix_", "Ljava/lang/String;");
  jstring s_val_prefix = (jstring) env->GetObjectField(bucketOptions, fid_prefix);

  // we have to get string bytes into C string
  const char *c_str_prefix;
  c_str_prefix = env->GetStringUTFChars (s_val_prefix, NULL);
  if (c_str_prefix == NULL) {
    return;
  }
  std::string prefix = c_str_prefix;

  // after using it, remember to release the memory
  env->ReleaseStringUTFChars (s_val_prefix, c_str_prefix);

  /*
   * Get dest_bucket.object_
   */
  // TODO: refactor this duplicated code
  jfieldID fid_object = env->GetFieldID(cls, "object_", "Ljava/lang/String;");
  jstring s_val_object = (jstring) env->GetObjectField(bucketOptions, fid_object);

  // we have to get string bytes into C string
  const char *c_str_object;
  c_str_object = env->GetStringUTFChars (s_val_object, NULL);
  if (c_str_object == NULL) {
    return;
  }
  std::string object_path = c_str_object;

  // after using it, remember to release the memory
  env->ReleaseStringUTFChars (s_val_object, c_str_object);

  /*
   * Get dest_bucket.region_
   */
  // TODO: refactor this duplicated code
  jfieldID fid_region = env->GetFieldID(cls, "region_", "Ljava/lang/String;");
  jstring s_val_region = (jstring) env->GetObjectField(bucketOptions, fid_region);

  // we have to get string bytes into C string
  const char *c_str_region;
  c_str_region = env->GetStringUTFChars (s_val_region, NULL);
  if (c_str_region == NULL) {
    return;
  }
  std::string region = c_str_region;

  // after using it, remember to release the memory
  env->ReleaseStringUTFChars (s_val_region, c_str_region);

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
