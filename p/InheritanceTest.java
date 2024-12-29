package p;

class A {
    int egg;
    static int baz = 3;
    static int bleh = 4;

    /*
    public int foo(int a, int b) {
        return a + b;
    }
    */
}

class B extends A {
    static int baz = 5;
    int horse;

    /*
    public int bar(int a) {
        return a * egg;
    }
    */
}

class InheritanceTest {
    static int test() {
        B b = new B();
        b.egg = 2;
        //return b.bar(b.foo(4, 3));

        return B.baz * A.baz;
    }

    static void static_test() {
        System.out.println("A:");
        System.out.println(A.baz);
        System.out.println(A.bleh);
        System.out.println("B:");
        System.out.println(B.baz);
        System.out.println(B.bleh);
    }

    static int instance_test() {
        B b = new B();
        b.egg = 1;
        b.horse = 2;

        System.out.println(b.egg);
        System.out.println(b.horse);

        b.egg = 3;
        b.horse = 4;

        System.out.println(b.egg);
        System.out.println(b.horse);

        return b.egg * b.horse;
    }

    public static void main() {
        instance_test();
    }
}
