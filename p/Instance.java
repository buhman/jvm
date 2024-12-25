package p;

class Instance {
    int a;
    int b;

    public Instance(int a) {
        this.a = a;
        this.b = 13;
    }

    int mul() {
        return a * b;
    }

    static int test() {
        Instance i = new Instance(12);
        return i.mul();
    }

    public static void main() {
        test();
    }
}
