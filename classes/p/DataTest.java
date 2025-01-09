package p;

import p.Data;

class DataTest {
    static void main() {
        test();
    }

    static int test() {
        return test2(6, 3) * 5;
    }

    static int test2(int a, int b) {
        return a - b;
    }
}
