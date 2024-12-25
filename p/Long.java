package p;

class Long {
    static long test(long n, long m) {
        long y = n + m; // 21
        long z = y % 9999; // 21
        long a = z * 5; // 105
        long b = a + 1; // 106
        long c = b / 3;
        long d = c & 0x0ffffffff0L; // 32
        long e = d | 0x1000000000L; // 68719476768 (16, 32)
        long f = e - 2; // 68719476766 (16, 30)
        long g = -f; // -68719476766 (-17, -30)
        long h = g >> 1;
        long i = h << 2;
        long j = i >>> 1;
        long k = j ^ 0xffffffffffffffffL; // -9223371968135299043
        return k;
    }

    static void test2(long a) {
        int b = (int)a;
        float c = (float)a;
        long d = (long)b;
        long e = (long)c;
    }

    static boolean test3(long a, long b) {
        boolean c = a > b;
        if (c) {
            return -a == b;
        } else {
            return -b <= a;
        }
    }

    static long test4() {
        long[] arr = {1, 2, 3, 4};
        long sum = 0;
        for (int i = 0; i < arr.length; i++) {
            sum += arr[i];
        }
        boolean b = sum > 1;
        return sum * 4; // 40
    }

    // -9223371968135299059
    // -2147483632
    // 13
    public static void main() {
        long a = test(10, 11);
        int b = (int)a;
        test2(10);
        test3(88, 123);
        test4();
    }
}
