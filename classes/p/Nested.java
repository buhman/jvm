package p;

class NestedFoo {
    public class NestedBar {
        public static int baz(int n) {
            return n + 10;
        }
    }
}

public class Nested {
    public static int test() {
        return NestedFoo.NestedBar.baz(42);
    }

    public static void main() {
        System.out.println(test());
    }
}
