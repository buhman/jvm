package p;

import java.util.ArrayList;

public class Test {
    public int foo(int a) {
        return a * 2;
    }

    public final String test = "asdf";
    public final int eggs = 1234;
    public final float bacon = 12.34f;

    public int bar = foo(eggs);

    public static float mul(float a, float b) {
        return a * b;
    }

    public static int comp(int a, int b) {
        if (a < b) {
            return a * 2;
        } else {
            return a * 4;
        }
    }

    public static void main(String[] args) {
        ArrayList<Integer> numbers = new ArrayList<Integer>();
        numbers.add(5);
        numbers.add(9);
        numbers.add(8);
        numbers.add(1);
        numbers.forEach( (n) -> { System.out.println(n); } );
    }
}
