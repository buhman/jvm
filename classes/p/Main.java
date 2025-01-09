package p;

class Main {
    public static int test2() {
        int[] num = {10, 20, 30, 40};
        int sum = 0;
        for (int i = 0; i < num.length; i++) {
            sum += num[i];
        }
        return sum + 1;
    }

    public static int test1() {
        int a = 6;
        int b = 7;
        int c = a * b;  // 42
        int d = c << 4; // 672
        int e = d + 11; // 683
        int f = e - 3;  // 680
        int g = f / 3;  // 226
        int h = g ^ 0x0fffffff; // 268435229
        char i = (char)h; // 65309
        return i;
    }

    public static void main(String[] args) {
        System.out.println(test2());
    }
}
