package p;

class LookupSwitch {
    static int foo(int a) {
        switch (a) {
        case 1:    return 5;
        case 10:   return 42;
        case 100:  return 432;
        case 1000: return 999;
        case 10000: return 9999;
        default: return 123;
        }
    }

    public static void main() {
        foo(10);
    }
}
