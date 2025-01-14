package test;

class TestParseInteger {
    public static void main() {
        System.out.println(Integer.parseInt("0", 10)); // returns 0
        System.out.println(Integer.parseInt("473", 10)); // returns 473
        System.out.println(Integer.parseInt("+42", 10)); // returns 42
        System.out.println(Integer.parseInt("-0", 10)); // returns 0
        System.out.println(Integer.parseInt("-FF", 16)); // returns -255
        System.out.println(Integer.parseInt("1100110", 2)); // returns 102
        System.out.println(Integer.parseInt("2147483647", 10)); // returns 2147483647
        System.out.println(Integer.parseInt("-2147483648", 10)); // returns -2147483648
        System.out.println(Integer.parseInt("2147483648", 10)); // throws a NumberFormatException
        System.out.println(Integer.parseInt("99", 8)); // throws a NumberFormatException
        System.out.println(Integer.parseInt("Kona", 10)); // throws a NumberFormatException
        System.out.println(Integer.parseInt("Kona", 27)); // returns 411787
    }
}
