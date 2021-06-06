package org.rocksdb;

public class DBCloud extends RocksDB {

  private DBCloud(final long nativeHandle) {
    super(nativeHandle);
  }

  /**
   * Open a DBCloud, similiar to {@link RocksDB#open(Options, String)}.
   *
   */
  public static DBCloud open(final Options options, final String name,
                             final String persistent_cache_path,
                             final long persistent_cache_size_gb, // TODO: uint64_t
                             boolean read_only) throws RocksDBException {

    // final DBCloud db = new DBCloud(open(options.nativeHandle_, path));
    //
    return new DBCloud(open(options.nativeHandle_, name,
                            persistent_cache_path, persistent_cache_size_gb,
                            read_only));
  }

  /*
   *
   * TODO:
   *
   * Status DBCloud::Open(const Options& options, const std::string& dbname,
   *                  const std::string& persistent_cache_path,
   *                  const uint64_t persistent_cache_size_gb, DBCloud** dbptr,
   *                  bool read_only);
   *
   * Status DBCloud::Open(const Options& opt, const std::string& local_dbname,
   *                  const std::vector<ColumnFamilyDescriptor>& column_families,
   *                  const std::string& persistent_cache_path,
   *                  const uint64_t persistent_cache_size_gb,
   *                  std::vector<ColumnFamilyHandle*>* handles, DBCloud** dbptr,
   *                  bool read_only);
   */

  private static native long open(final long optionHandle, final String name,
        final String persistence_cache_path, final long persistent_cache_size_gb,
        final boolean read_only) throws RocksDBException;
  @Override protected final native void disposeInternal(final long handle);
}
