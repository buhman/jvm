package p;

class TestPrimitiveArray {
    static boolean testBool() {
        boolean[] a = {true, false, true, false, true};
        int sum = 0;
        for (int i = 0; i < a.length; i++) {
            if (a[i] == true) {
                sum += 1;
            } else {
                sum -= 1;
            }
        }
        return sum == 1;
    }

    static boolean testByte() {
        byte[] a = {1, -1, 3, 4};
        int sum = 0;
        for (int i = 0; i < a.length; i++) {
            sum += a[i];
        }
        return sum == 7;
    }

    static boolean testChar() {
        char[] a = {'a', 'b', 'c', 'd'};
        return
            a[0] == 'a' &&
            a[1] == 'b' &&
            a[2] == 'c' &&
            a[3] == 'd';
    }

    static boolean testShort() {
        short[] a = {-1234, 1234, 300, 400};
        int sum = 0;
        for (int i = 0; i < a.length; i++) {
            sum += a[i];
        }
        return sum == 700;
    }

    static boolean testInt() {
        int[] a = {-12345678, 12345678, 3000000, 4000000};
        int sum = 0;
        for (int i = 0; i < a.length; i++) {
            sum += a[i];
        }
        return sum == 7000000;
    }

    static boolean epsilon(float a, float b) {
        return Math.abs(a - b) < 0.0001f;
    }

    static boolean testFloat() {
        float[] a = {1.2f, -1.2f, 3.4f, 5.6f};
        float sum = 0;
        for (int i = 0; i < a.length; i++) {
            sum += a[i];
        }
        return epsilon(sum, 9.0f);
    }

    static boolean testLong() {
        long[] a = {800000000000L, -800000000000L, 300000000000L, 400000000000L};
        long sum = 0;
        for (int i = 0; i < a.length; i++) {
            sum += a[i];
        }
        return sum == 700000000000L;
    }

    static boolean testDouble() {
        double[] a = {9007199254740900.0, -1.0};
        double sum = 0;
        for (int i = 0; i < a.length; i++) {
            sum += a[i];
        }
        return sum == 9007199254740899.0;
    }

    public static void main() {
        System.out.print("bool: ");
        System.out.println(testBool());
        System.out.print("byte: ");
        System.out.println(testByte());
        System.out.print("char: ");
        System.out.println(testChar());
        System.out.print("short: ");
        System.out.println(testShort());
        System.out.print("int: ");
        System.out.println(testInt());
        System.out.print("long: ");
        System.out.println(testLong());
        System.out.print("double: ");
        System.out.println(testDouble());
    }
}
