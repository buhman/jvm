package p;

import java.nio.ByteOrder;

class TestByteOrder {
    public static boolean test() {
        return ByteOrder.nativeOrder() == ByteOrder.LITTLE_ENDIAN;
    }
    public static void main() {
        test();
    }
}
