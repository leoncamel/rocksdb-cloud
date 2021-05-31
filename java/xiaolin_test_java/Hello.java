
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

    CloudEnvOptions cloudEnvOptions = new CloudEnvOptions();

    System.out.println(cloudEnvOptions);
  }
}
