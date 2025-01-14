package test;

class TestIntegerDecode {
    public static void main() {
        System.out.println(Integer.decode("-#12aff1e1"));
        System.out.println(Integer.decode("-0x3c07714b"));
        System.out.println(Integer.decode("-0X3bbbfcef"));
        System.out.println(Integer.decode("0x7eb38fbd"));
        System.out.println(Integer.decode("-0X4a2db9bb"));

        System.out.println(Integer.decode("02637651"));

        System.out.println(Integer.decode("2637651"));


        /*
          -313520609
          -1007120715
          -1002175727
          2125696957
          -1244510651
          737193
          2637651
        */
    }
}
