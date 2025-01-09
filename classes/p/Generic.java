package p;

class Generic<T, U>
{
    T obj1;  // An object of type T
    U obj2;  // An object of type U

    // constructor
    Generic(T obj1, U obj2)
    {
        this.obj1 = obj1;
        this.obj2 = obj2;
    }

    // To print objects of T and U
    public static void print()
    {
        float ff = 1.0f;
        Float f = new Float(f);
        Generic<Integer, Float> g = new Generic<Integer, Float>(1, f);
    }
}
