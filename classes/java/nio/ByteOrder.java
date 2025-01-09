package java.nio;

import java.misc.Memory;

public class ByteOrder {
    public static final ByteOrder BIG_ENDIAN = new ByteOrder();
    public static final ByteOrder LITTLE_ENDIAN = new ByteOrder();

    private static final ByteOrder NATIVE_ORDER =
        Memory.isBigEndian() ? ByteOrder.BIG_ENDIAN : ByteOrder.LITTLE_ENDIAN;

    public static ByteOrder nativeOrder() {
        return NATIVE_ORDER;
    }
}
