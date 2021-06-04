
import org.rocksdb.DBOptions;
import org.rocksdb.CloudEnvOptions;

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
  }
}
