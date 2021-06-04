// Copyright (c) 2021-present, DataCanvas, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).


package org.rocksdb;

/**
 * CloudEnvOptions to control the behavior of a rocksdb-cloud database instances.
 *
 * TODO: Add more docs
 */
public class CloudEnvOptions extends RocksObject {
  static {
    RocksDB.loadLibrary();
  }

  /**
   * Construct with default Options
   */
  public CloudEnvOptions() {
    super(newCloudEnvOptions());
  }

  /**
   * Override AWS endpoint.
   *
   * @param endpoint the AWS S3's endpoint address, for example, "http://127.0.0.1:9000".
   *
   * @return the reference to these options.
   */
  public CloudEnvOptions setEndpointOverride(final String endpoint) {
    setEndpointOverride(nativeHandle_, endpoint);
    return this;
  }

  public String endpointOverride() {
    return getEndpointOverride(nativeHandle_);
  }

  public CloudEnvOptions setSrcBucketOptions(final BucketOptions bucketOptions) {
    setSrcBucketOptions(nativeHandle_, bucketOptions);
    return this;
  }

  public BucketOptions srcBucketOptions() {
    // TODO:
    return new BucketOptions();
  }

  // native functions
  private native static long newCloudEnvOptions();
  @Override protected final native void disposeInternal(final long handle);

  private native static void setEndpointOverride(final long handle, final String endpoint);
  private native static String getEndpointOverride(final long handle);

  private native static void setSrcBucketOptions(final long handle, BucketOptions srcBucketOptions);
  private native static BucketOptions getSrcBucketOptions(final long handle);

  private native static void setDestBucketOptions(final long handle, BucketOptions destBucketOptions);
  private native static BucketOptions getDestBucketOptions(final long handle);
}
