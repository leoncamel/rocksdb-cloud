
import org.rocksdb.DBOptions;
import org.rocksdb.CloudEnvOptions;
import org.rocksdb.CloudEnv;
import org.rocksdb.Options;
import org.rocksdb.DBCloud;

class Hello {
  public static void main(final String[] args) {
    System.out.println("Hello from Hello Class");

    DBOptions origOpts = new DBOptions();
    origOpts.setCreateIfMissing(true);
    origOpts.setAllow2pc(true);
    origOpts.setMaxBackgroundJobs(100);

    System.out.println(origOpts);

    testCloudEnvOptions();
  }

  public static void testCloudEnvOptions() {
    CloudEnvOptions cloudEnvOptions = new CloudEnvOptions();
    String tmpEndpointAddr = "http://192.168.1.3:9090";

    cloudEnvOptions.setEndpointOverride(tmpEndpointAddr);

    System.out.println(cloudEnvOptions);
    System.out.println(cloudEnvOptions.endpointOverride());

    assert tmpEndpointAddr == cloudEnvOptions.endpointOverride();

    CloudEnv ce = new CloudEnv(cloudEnvOptions);
    System.out.println(ce.getNativeHandle());

    assert ce.getNativeHandle() != 0;

    Options opts = new Options();
    opts.setEnv(ce);
    opts.setCreateIfMissing(true);

    assert opts.getEnv().getNativeHandle() == ce.getNativeHandle();

    String kDBPath = "/tmp/rocksdb_cloud_durable";
    String persist_path = "";
    try {
      DBCloud db_cloud = DBCloud.open(opts, kDBPath, persist_path, 0, false);
      assert db_cloud.getNativeHandle() > 0;
      System.out.println("DBCloud Instance " + db_cloud);
      System.out.println(db_cloud.getNativeHandle());
    } catch(Exception e) {
      e.printStackTrace();
    }
  }
}
