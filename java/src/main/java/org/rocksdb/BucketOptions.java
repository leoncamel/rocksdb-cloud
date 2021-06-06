package org.rocksdb;

public class BucketOptions {

  public String bucket;
  public String prefix;
  public String object;
  public String region;
  public String name;

  public BucketOptions() {
    this.bucket = "";
    this.prefix = "";
    this.object = "";
    this.region = "";
    this.name = "";
  }

  @Override
  public boolean equals(final Object o) {
    if (this == o) {
      return true;
    }

    if (o == null || getClass() != o.getClass()) {
      return false;
    }

    final BucketOptions bucketOptions = (BucketOptions) o;

    return bucketOptions.bucket == bucket &&
      bucketOptions.prefix == prefix &&
      bucketOptions.object == object &&
      bucketOptions.region == region &&
      bucketOptions.name == name;
  }

  @Override
  public int hashCode() {
    return bucket.hashCode() * prefix.hashCode()
      * object.hashCode() * region.hashCode()
      * name.hashCode();
  }
}
