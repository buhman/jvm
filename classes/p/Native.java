package p;

import java.misc.Memory;

class Native {
    public static void main() {
        String foo = "hello Dreamcast";
        System.out.println(foo);

        int address = 0x1234;
        int value = 0x5678;
        Memory.putU4(address, value);
    }
}
