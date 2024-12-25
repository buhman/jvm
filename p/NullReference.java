package p;

class NullReference {
    int field;

    static int test() {
        Object o = null;
        if (o == null)
            return 1;
        else
            return 0;
    }

    static NullReference test2(NullReference r) {
        NullReference b = new NullReference();
        b.field = 39;
        return b;
    }

    static int test3() {
        NullReference a = new NullReference();
        a.field = 12;
        NullReference c = test2(a);

        if (a != c)
            c.field += 1000;

        return c.field;
    }

    static int test4() {
        Object[] oa = new Object[10];
        for (int i = 0; i < oa.length; i++) {
            if (i % 2 == 0)
                oa[i] = null;
            else
                oa[i] = new Object();
        }
        int count = 0;
        for (int i = 0; i < oa.length; i++) {
            if (oa[i] == null)
                count += 1;
        }
        return count;
    }

    public static void main() {
        test4();
        test3();
    }
}
