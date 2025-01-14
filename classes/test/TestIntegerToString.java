package test;

class TestIntegerToString {
    public static void main() {
        System.out.println(Integer.toString(0x12aff1e1, 16));
        System.out.println(Integer.toString(-0x3c07714b, 16));
        System.out.println(Integer.toString(0x3bbbfcef, 16));
        System.out.println(Integer.toString(-0x7eb38fbd, 16));
        System.out.println(Integer.toString(-0x4a2db9bb, 16));

        System.out.println(Integer.toString(02637651, 8));

        System.out.println(Integer.toString(2637651, 10));

        System.out.println(Integer.toString(0b111101111, 2));


        /*
          12aff1e1
          -3c07714b
          3bbbfcef
          -7eb38fbd
          -4a2db9bb
          2637651
          2637651
          111101111
        */
    }
}
