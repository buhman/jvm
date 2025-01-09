package p;

class Super {
    public int aa;
    public int bb;

    int bar() {
        return bb;
    }
};

class Fields extends Super {
    public int cc;
    public int dd;

    int foo() {
        return bar();
    }
}

class InstanceFields {
    public static int test() {
        Fields f = new Fields();
        f.aa = 11;
        f.bb = 22;
        f.cc = 33;
        f.dd = 44;

        return f.foo();
        //return f.bb;
    }

    public static void main() {
        test();
    }
}
