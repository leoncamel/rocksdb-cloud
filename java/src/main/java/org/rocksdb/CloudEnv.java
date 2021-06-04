package org.rocksdb;

/**
 * HDFS environment.
 */
public class CloudEnv extends Env {

  /**
   <p>Creates a new environment that is used for Cloud environment.</p>
   *
   * <p>The caller must delete the result when it is
   * no longer needed.</p>
   *
   * @param coptions an CloudEnvOptions for createing CloudEnv.
   */
  public CloudEnv(final CloudEnvOptions coptions) {
    super(createCloudEnv(coptions.nativeHandle_));
  }

  /*
   * TODO:
   *   // Create a new AWS cloud env Status
   *   CloudEnv* cenv;
   *   Status s = CloudEnv::NewAwsEnv(Env::Default(), kBucketSuffix, kDBPath,
   *                              kRegion, kBucketSuffix, kDBPath, kRegion,
   *                              cloud_env_options, nullptr, &cenv);
   */
  private static native long createCloudEnv(final long cloud_env_options_handle);
  @Override protected final native void disposeInternal(final long handle);
}
