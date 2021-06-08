

package org.rocksdb;

public enum LogType {
    LogNone((byte)0x00),
    LogKinesis((byte)0x01),
    LogKafka((byte)0x02),
    LogEnd((byte)0x3);

    private byte value;

    LogType(final byte value) {
        this.value = value;
    }

    public byte getValue() {
        return value;
    }

    public static LogType getLogType(final byte byteIdentifier) {
        for (final LogType logType : LogType.values()) {
            if (logType.getValue() == byteIdentifier) {
                return logType;
            }
        }

        throw new IllegalArgumentException("Illegal value provided for LogType.");
    }
}
