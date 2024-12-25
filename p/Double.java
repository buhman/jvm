package p;

class Double {
    public static void main() {
        test();
        test2();
        test3(3.0);
    }

    static double test() {
        double a = 1.0;
        double b = a / 3.0;
        double c = b * 2.0;
        double d = c + 5.0;
        double e = d - 0.5;
        double f = -e;
        double g = f % 2.0;
        int h = (int)g;
        return h;
    }

    static double test2() {
        double[] arr = {1.0, 2.1, 3.2, 4.3};
        double sum = 0;
        for (int i = 0; i < arr.length; i++) {
            sum += arr[i];
        }
        boolean b = sum < 1.0;
        double i = 0.0;
        if (b)
            i = 1.0;
        return i * 4.2;
    }

    static double test3(double n) {
        float a = (float)n;
        int b = (int)n;
        long c = (long)n;
        char d = (char)n;

        double e = (double)a;
        double f = (double)b;
        double g = (double)c;
        double h = (double)d;

        return e * f * g * h;
    }
}
