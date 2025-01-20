package java.nio;

import jvm.internal.Memory;

public class ByteOrder {
    public static final ByteOrder BIG_ENDIAN = new ByteOrder();
    public static final ByteOrder LITTLE_ENDIAN = new ByteOrder();

    private static final ByteOrder NATIVE_ORDER =
        Memory.isBigEndian() ? ByteOrder.BIG_ENDIAN : ByteOrder.LITTLE_ENDIAN;

    public static ByteOrder nativeOrder() {
        return NATIVE_ORDER;
    }

    public String toString() {
        if (this == BIG_ENDIAN) {
            return "BIG_ENDIAN";
        } else {
            return "LITTLE_ENDIAN";
        }
    }
}
