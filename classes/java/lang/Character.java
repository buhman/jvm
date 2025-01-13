package java.lang;

class Character
    implements Comparable<Character> {
    public static final int MAX_RADIX = 36;

    public static final int MAX_VALUE = '\uFFFF';

    public static final int MIN_RADIX = 2;

    public static final char MIN_VALUE = '\u0000';

    public static final int SIZE = 16;

    private final char value;

    public Character(char value) {
        this.value = value;
    }

    public char charValue() {
        return value;
    }

    public int compareTo(Character anotherCharacter) {
        return this.charValue() - anotherCharacter.charValue();
    }

    private static int _digit(char ch) {
        if (Character.isDigit(ch))
            return (char)((int)ch - (int)'0');
        if (ch >= 'A' && ch <= 'Z')
            return (char)((int)ch - (int)'A' + 10);
        if (ch >= 'a' && ch <= 'z')
            return (char)((int)ch - (int)'a' + 10);
        return -1;
    }

    public static int digit(char ch, int radix) {
        if (radix < MIN_RADIX || radix > MAX_RADIX)
            return -1;
        int value = _digit(ch);
        return (value < radix) ? value : -1;
    }

    public boolean equals(Object obj) {
        return obj instanceof Character && value == ((Character)obj).value;
    }

    public static char forDigit(int digit, int radix) {
        if (digit < 0 || digit > MAX_RADIX)
            return '\u0000';
        if (digit < 10) {
            return (char)((int)'0' + digit);
        } else {
            return (char)((int)'a' + digit - 10);
        }
    }

    public int hashCode() {
        return value;
    }

    public static boolean isDigit(char ch) {
        return ch >= '0' && ch <= '9';
    }

    public static boolean isISOControl(char ch) {
        return (ch >= '\u0000' && ch <= '\u001F') || (ch >= '\u007F' && ch <= '\u009F');
    }

    public static boolean isLowerCase(char ch) {
        return
            (ch >= 'a' && ch <= 'z') ||
            (ch >= '\u00DF' && ch <= '\u00F6') ||
            (ch >= '\u00F8' && ch <= '\u00FF');
    }

    public static boolean isSpaceChar(char ch) {
        switch (ch) {
        case ' ':  return true;
        case '\t': return true;
        case '\n': return true;
        case '\r': return true;
        case '\f': return true;
        default: return false;
        }
    }

    public static boolean isUpperCase(char ch) {
        return
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= '\u00C0' && ch <= '\u00D6') ||
            (ch >= '\u00D8' && ch <= '\u00DE');
    }

    public static boolean isWhitespace(char ch) {
        switch (ch) {
        case ' ':      return true;
        case '\t':     return true;
        case '\n':     return true;
        case '\u000B': return true;
        case '\u000C': return true;
        case '\r':     return true;
        case '\u001C': return true;
        case '\u001D': return true;
        case '\u001E': return true;
        case '\u001F': return true;
        default: return false;
        }
    }

    public static char toLowerCase(char ch) {
        if (ch >= 'A' && ch <= 'Z')
            return (char)((int)ch - (int)'A' + (int)'a');
        if (ch >= '\u00C0' && ch <= '\u00D6')
            return (char)((int)ch - (int)'\u00C0' + (int)'\u00E0');
        if (ch >= '\u00D8' && ch <= '\u00DE')
            return (char)((int)ch - (int)'\u00D8' + (int)'\u00F8');
        return ch;
    }

    public String toString() {
        return Character.toString(value);
    }

    public static String toString(char c) {
        return new String(new char[] { c });
    }

    public static char toUpperCase(char ch) {
        if (ch >= 'a' && ch <= 'z')
            return (char)((int)ch - (int)'a' + (int)'A');
        if (ch >= '\u00E0' && ch <= '\u00F6')
            return (char)((int)ch - (int)'\u00E0' + (int)'\u00C0');
        if (ch >= '\u00F8' && ch <= '\u00FE')
            return (char)((int)ch - (int)'\u00F8' + (int)'\u00D8');
        return ch;
    }

    public static Character valueOf(char c) {
        return new Character(c);
    }
}
