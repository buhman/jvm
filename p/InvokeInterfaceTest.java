package p;

interface Op {
    public int op(int a, int b);
}

class Foo implements Op {
    public int op(int a, int b) {
        return a + b;
    }
}

public class InvokeInterfaceTest {
    static int test(Op operator) {
        return operator.op(5, 10);
    }

    public static void main() {
        test(new Foo());
    }
}
