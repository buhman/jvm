package test;

class Test<T> {
    T obj;

    Test(T obj) {
        this.obj = obj;
    }

    public T getObject() {
        return this.obj;
    }
}

class TestGeneric {
    public static void main(String[] args)
    {
        Test<Integer> ti = new Test<Integer>(15);
        System.out.println(ti.getObject());

        Test<String> ts = new Test<String>("GeeksForGeeks");
        System.out.println(ts.getObject());
    }
}
