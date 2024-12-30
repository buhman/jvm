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

    public static void main() {
        test();
    }
}
