package org.rocksdb;

public class DBCloud extends RocksDB {

  private DBCloud(final long nativeHandle) {
    super(nativeHandle);
  }

  /**
   * Open a DBCloud, similiar to {@link RocksDB#open(Options, String)}.
   *
   */
  public static DBCloud open(final Options options, final String path) {
    // final DBCloud db = new DBCloud(open(options.nativeHandle_, path));
    //
    return null;
  }
}
