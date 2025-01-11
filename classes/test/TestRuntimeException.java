package test;

class TestRuntimeException {
    public static void testAA1() {
        Object[] a = null;
        Object b = a[0];
    }

    public static void testAA2() {
        Object[] a = new Object[1];
        Object b = a[42];
    }

    public static void testAA3() {
        Object[] a = null;
        a[0] = null;
    }

    public static void testAA4() {
        Object[] a = new Object[1];
        a[42] = null;
    }

    public static void test5() {
        Object[] a = new Object[-5];
    }

    public static void test6() {
        Object[] a = null;
        int b = a.length;
    }

    public static void test7() throws Exception {
        Exception e = null;
        throw e;
    }

    public static void testBA1() {
        byte[] a = null;
        byte b = a[0];
    }

    public static void testBA2() {
        byte[] a = new byte[1];
        byte b = a[42];
    }

    public static void testBA3() {
        byte[] a = null;
        a[0] = 0;
    }

    public static void testBA4() {
        byte[] a = new byte[1];
        a[42] = 0;
    }

    public static void testCA1() {
        char[] a = null;
        char b = a[0];
    }

    public static void testCA2() {
        char[] a = new char[1];
        char b = a[42];
    }

    public static void testCA3() {
        char[] a = null;
        a[0] = 0;
    }

    public static void testCA4() {
        char[] a = new char[1];
        a[42] = 0;
    }

    public static void testCC() {
        NullPointerException a = new NullPointerException();
        Object b = a;
        ArrayIndexOutOfBoundsException c = (ArrayIndexOutOfBoundsException)b;
    }

    public static void testDA1() {
        double[] a = null;
        double b = a[0];
    }

    public static void testDA2() {
        double[] a = new double[1];
        double b = a[42];
    }

    public static void testDA3() {
        double[] a = null;
        a[0] = 0;
    }

    public static void testDA4() {
        double[] a = new double[1];
        a[42] = 0;
    }

    public static void testFA1() {
        float[] a = null;
        float b = a[0];
    }

    public static void testFA2() {
        float[] a = new float[1];
        float b = a[42];
    }

    public static void testFA3() {
        float[] a = null;
        a[0] = 0;
    }

    public static void testFA4() {
        float[] a = new float[1];
        a[42] = 0;
    }

    public static void testIA1() {
        int[] a = null;
        int b = a[0];
    }

    public static void testIA2() {
        int[] a = new int[1];
        int b = a[42];
    }

    public static void testIA3() {
        int[] a = null;
        a[0] = 0;
    }

    public static void testIA4() {
        int[] a = new int[1];
        a[42] = 0;
    }

    public static void testidiv() {
        int a = 42;
        int b = 0;
        int c = a / b;
    }

    public static void testirem() {
        int a = 42;
        int b = 0;
        int c = a % b;
    }

    public static void testldiv() {
        long a = 42;
        long b = 0;
        long c = a / b;
    }

    public static void testlrem() {
        long a = 42;
        long b = 0;
        long c = a % b;
    }

    public static void testLA1() {
        long[] a = null;
        long b = a[0];
    }

    public static void testLA2() {
        long[] a = new long[1];
        long b = a[42];
    }

    public static void testLA3() {
        long[] a = null;
        a[0] = 0;
    }

    public static void testLA4() {
        long[] a = new long[1];
        a[42] = 0;
    }

    public static void testmultianewarray() {
        int[][] a = new int[-1][-1];
    }

    public static void testnewarray() {
        int[] a = new int[-1];
    }

    public static void testSA1() {
        short[] a = null;
        short b = a[0];
    }

    public static void testSA2() {
        short[] a = new short[1];
        short b = a[42];
    }

    public static void testSA3() {
        short[] a = null;
        a[0] = 0;
    }

    public static void testSA4() {
        short[] a = new short[1];
        a[42] = 0;
    }

    public static void main() throws Exception {
        //testAA1();
        //testAA2();
        //testAA3();
        //testAA4();
        //test5();
        //test6();
        //test7();
        //testBA1();
        //testBA2();
        //testBA3();
        //testBA4();
        //testCA1();
        //testCA2();
        //testCA3();
        //testCA4();
        //testCC();
        //testDA1();
        //testDA2();
        //testDA3();
        //testDA4();
        //testFA1();
        //testFA2();
        //testFA3();
        //testFA4();
        //testIA1();
        //testIA2();
        //testIA3();
        //testIA4();
        //testidiv();
        //testirem();
        //testldiv();
        //testlrem();
        //testLA1();
        //testLA2();
        //testLA3();
        //testLA4();
        //testmultianewarray();
        //testnewarray();
        //testSA1();
        //testSA2();
        //testSA3();
        //testSA4();
    }
}
