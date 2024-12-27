package p;

class ClassA {
}

class InstanceOf {
    static boolean test() {
        ClassA ca = new ClassA();
        Object a = ca;

        return (ca instanceof ClassA);
    }

    public static void main() {
        test();
    }
}
