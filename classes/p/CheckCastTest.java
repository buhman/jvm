package p;

class Animal {
}

class Cat extends Animal {
}

class Dog extends Animal {
}

class CheckCastTest {
    public static boolean test() {
        Dog d = new Dog();
        Cat c = new Cat();
        Animal da = d;
        Animal ca = c;
        Cat cc = (Cat)da;
        //Cat cc = (Cat)ca;
        return cc instanceof Cat;
    }

    public static boolean arrayTest() {
        Dog[][] d = new Dog[1][1];
        Cat[][] c = new Cat[1][1];
        Animal[][] da = d;
        Animal[][] ca = c;
        //Cat[][] cc = (Cat[][])da;
        Cat[][] cc = (Cat[][])ca;
        return cc instanceof Cat[][];
    }

    public static boolean arrayTest2() {
        Cat[] c = new Cat[1];
        c[0] = new Cat();
        return c instanceof Cat[];
    }

    public static void main() {
        //test();
        arrayTest2();
        //System.out.println(arrayTest());
    }
}
