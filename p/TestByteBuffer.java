package p;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

class TestByteBuffer {

    public static int test() {
        byte[] a = new byte[10];
        a[0] = 42;
        a[1] = 0x12;
        a[2] = 0x34;
        a[3] = 0x56;
        a[4] = 0x78;

        ByteBuffer buf = ByteBuffer.wrap(a).order(ByteOrder.LITTLE_ENDIAN);
        buf.get();
        int b = buf.getInt();
        return b;
    }


    public static void main() {
        test();
    }
}
