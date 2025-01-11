package test;

class A {
    int egg;
    static int baz = 3;
    static int bleh = 4;

    public A() {
        egg = -1;
    }

    public int foo(int a) {
        return a + baz;
    }
}

class B extends A {
    static int baz = 5;
    int horse;

    public int bar(int a) {
        return a * egg;
    }
}

class TestInheritance {

    static void static_test() {
        System.out.println("A:");
        System.out.println(A.baz);
        System.out.println(A.bleh);
        System.out.println("B:");
        System.out.println(B.baz);
        System.out.println(B.bleh);

        B.bleh = 33;
        B.baz = 99;
        System.out.println("A:");
        System.out.println(A.baz);
        System.out.println(A.bleh);
        System.out.println("B:");
        System.out.println(B.baz);
        System.out.println(B.bleh);

        /*
          static_test:
          A:
          3
          4
          B:
          5
          4
          A:
          3
          33
          B:
          99
          33
        */
    }

    static int instance_test() {
        B b = new B();
        System.out.println(b.egg);
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

    static int method_test() {
        B b = new B();
        b.egg = 5;
        return b.foo(b.bar(6));
    }

    public static void main() {
        System.out.println("static_test:");
        static_test();
        /*
        System.out.println("instance_test:");
        System.out.println(instance_test());
        System.out.println("method_test:");
        method_test();
        */
    }
}
