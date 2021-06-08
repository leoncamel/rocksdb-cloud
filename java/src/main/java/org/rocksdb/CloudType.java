
package org.rocksdb;

public enum CloudType {
    CloudNone((byte)0x00),
    CloudAws((byte)0x01),
    CloudGoogle((byte)0x02),
    CloudAzure((byte)0x03),
    CloudRackspace((byte)0x04),
    CloudEnd((byte)0x05);

    private byte value;

    CloudType(final byte value) {
        this.value = value;
    }

    public byte getValue() {
        return value;
    }

    public static CloudType getCloudType(final byte byteIdentifier) {
        for (final CloudType cloudType : CloudType.values()) {
            if (cloudType.getValue() == byteIdentifier) {
                return cloudType;
            }
        }

        throw new IllegalArgumentException("Illegal value provided for CloudType.");
    }
}
