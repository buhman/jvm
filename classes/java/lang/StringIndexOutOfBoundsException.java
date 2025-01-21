package java.lang;

public class StringIndexOutOfBoundsException extends IndexOutOfBoundsException {

    public StringIndexOutOfBoundsException() {
        super();
    }

    public StringIndexOutOfBoundsException(int index) {
        super(Integer.toString(index));
    }

    public StringIndexOutOfBoundsException(String s) {
        super(s);
    }
}
