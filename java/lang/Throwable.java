package java.lang;

public class Throwable {
    private Object backtrace;
    private String message;
    private Throwable cause = this;

    public Throwable() {
    }

    public Throwable(String message) {
        this.message = message;
    }

    public Throwable(String message, Throwable cause) {
        this.message = message;
        this.cause = cause;
    }

    public Throwable(Throwable cause) {
        this.cause = cause;
    }

    public String toString() {
        return message;
    }
}
