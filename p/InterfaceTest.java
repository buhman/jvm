package p;

class InterfaceTest implements Interface
{
    public static int test()
    {
        InterfaceTest it = new InterfaceTest();
        System.out.println(it.a);
        Interface.a = "1234";
        return (int)it.a.getBytes()[0];
    }

    public static void main()
    {
        test();
    }
}
