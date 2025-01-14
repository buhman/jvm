package java.lang;

public class ArrayIndexOutOfBoundsException extends IndexOutOfBoundsException {

    ArrayIndexOutOfBoundsException() {
        super();
    }

    ArrayIndexOutOfBoundsException(int index) {
        super(String.valueOf(index));
    }

    ArrayIndexOutOfBoundsException(String s) {
        super(s);
    }
}
