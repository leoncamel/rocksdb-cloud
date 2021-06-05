
#include <jni.h>

#include "include/org_rocksdb_DBCloud.h"
#include "rocksdb/cloud/db_cloud.h"
#include "rocksdb/options.h"
#include "rocksjni/portal.h"

/*
 * Class:     org_rocksdb_DBCloud
 * Method:    open
 * Signature: (JLjava/lang/String;Ljava/lang/String;JZ)J
 */
JNIEXPORT jlong JNICALL Java_org_rocksdb_DBCloud_open
  (JNIEnv* env, jclass, jlong opt_jhandle, jstring path, jstring persist_path, jlong persist_cache_size_gb, jboolean readonly) {

  auto *opts = reinterpret_cast<ROCKSDB_NAMESPACE::Options*>(opt_jhandle);

  const char *c_str_path;
  c_str_path = env->GetStringUTFChars (path, NULL);
  if (c_str_path == NULL) {
    // TODO: Throws Exception
    return -1;
  }
  std::string s_path = c_str_path;
  env->ReleaseStringUTFChars (path, c_str_path);

  const char *c_str_persist_path;
  c_str_persist_path = env->GetStringUTFChars (persist_path, NULL);
  if (c_str_persist_path == NULL) {
    // TODO: Throws Exception
    return -1;
  }
  std::string s_persist_path = c_str_persist_path;
  env->ReleaseStringUTFChars (persist_path, c_str_persist_path);

  // long persist_cache_size_gb = env->Get
  uint64_t sz = persist_cache_size_gb > 0 ? persist_cache_size_gb : 0;

  ROCKSDB_NAMESPACE::DBCloud* db_cloud;
  ROCKSDB_NAMESPACE::Status s =
    ROCKSDB_NAMESPACE::DBCloud::Open(*opts, s_path, s_persist_path, sz, &db_cloud, readonly);
  if (!s.ok()) {
    // TODO: Throw Exception
    return -1;
  }

  return reinterpret_cast<jlong>(db_cloud);
}

/*
 * Class:     org_rocksdb_DBCloud
 * Method:    disposeInternal
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_rocksdb_DBCloud_disposeInternal
  (JNIEnv *, jobject, jlong jhandle) {
  auto *eo = reinterpret_cast<ROCKSDB_NAMESPACE::DBCloud*>(jhandle);
  assert(eo != nullptr);
  delete eo;
}
