
import org.rocksdb.DBOptions;
import org.rocksdb.Options;
import org.rocksdb.CloudEnvOptions;
import org.rocksdb.CloudEnv;
import org.rocksdb.DBCloud;
import org.rocksdb.BucketOptions;
import org.rocksdb.CloudType;
import org.rocksdb.LogType;
import java.util.HashMap;
import java.util.Map;

class Hello {
  public static void main(final String[] args) {
    System.out.println("Hello from Hello Class");

    DBOptions origOpts = new DBOptions();
    origOpts.setCreateIfMissing(true);
    origOpts.setAllow2pc(true);
    origOpts.setMaxBackgroundJobs(100);

    System.out.println(origOpts);

    for (int i = 0; i < 1000; i++) {
      testCloudEnvOptions();

      // Thread.sleep(1);
    }
  }

  public static void testCloudEnvOptions() {
    CloudEnvOptions cloudEnvOptions = new CloudEnvOptions();
    String tmpEndpointAddr = "http://172.20.3.242:9000";

    cloudEnvOptions.setEndpointOverride(tmpEndpointAddr);

    BucketOptions src_bucket = new BucketOptions();
    src_bucket.bucket = "cloud.durable.example";
    src_bucket.prefix = "rockset";
    src_bucket.object = "objpath";
    src_bucket.region = "";

    BucketOptions dest_bucket = new BucketOptions();
    dest_bucket.bucket = "cloud.durable.example";
    dest_bucket.prefix = "rockset";
    dest_bucket.object = "objpath";
    dest_bucket.region = "";

    cloudEnvOptions.setSrcBucketOptions(src_bucket);
    cloudEnvOptions.setDestBucketOptions(dest_bucket);

    // cloudEnvOptions.setCloudType(CloudType.CloudNone);
    // assert cloudEnvOptions.cloudType() == CloudType.CloudNone;
    cloudEnvOptions.setLogType(LogType.LogKafka);
    assert cloudEnvOptions.logType() == LogType.LogKafka;

    cloudEnvOptions.setKeepLocalLogFiles(false);

    HashMap<String, String> kafka_options = new HashMap<String, String>() {{
        put("metadata.broker.list", "172.20.3.83:9092");
    }};
    cloudEnvOptions.setKafkaLogOptions(kafka_options);


    System.out.println(cloudEnvOptions);
    System.out.println(cloudEnvOptions.endpointOverride());

    assert tmpEndpointAddr == cloudEnvOptions.endpointOverride();

    CloudEnv ce = new CloudEnv(cloudEnvOptions);
    System.out.println(ce.getNativeHandle());

    assert ce.getNativeHandle() != 0;

    Options opts = new Options();
    opts.setEnv(ce);
    // ce.disOwnNativeHandle();

    opts.setCreateIfMissing(true);

    assert opts.getEnv().getNativeHandle() == ce.getNativeHandle();

    String kDBPath = "/tmp/rocksdb_cloud_durable";
    String persist_path = "";
    try (final DBCloud db = DBCloud.open(opts, kDBPath, persist_path, 0, false)) {
      assert db.getNativeHandle() > 0;
      System.out.println("DBCloud Instance " + db);
      System.out.println(db.getNativeHandle());

      for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
          String key = String.format("%08dx%08d", i, j);
          String val = String.format("%016d", i * j);
          db.put(key.getBytes(), val.getBytes());
        }
        System.out.println(String.format("%08d 00000000", i));
      }

      // System.out.println(ce);
    } catch(Exception e) {
      e.printStackTrace();
    }
  }
}
