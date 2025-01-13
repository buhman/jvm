package java.lang;


public final class String
    implements Comparable<String>, CharSequence {

    private final char[] value;

    public String() {
        value = new char[0];
    }

    public String(byte[] bytes) {
        this(bytes, 0, bytes.length);
    }

    public String(byte[] bytes, int offset, int length) {
        value = new char[length];
        int i = 0;
        while (length > 0) {
            value[i] = (char)bytes[offset];
            i += 1;
            offset += 1;
            length -= 1;
        }
    }

    public String(char[] value) {
        this(value, 0, value.length);
    }

    public String(char[] value, int offset, int count) {
        this.value = new char[count];
        int i = 0;
        while (count > 0) {
            this.value[i] = value[offset];
            i += 1;
            offset += 1;
            count -= 1;
        }
    }

    public String(String original) {
        // shallow copy
        value = original.value;
    }

    public char charAt(int index) {
        return value[index];
    }

    public int compareTo(String anotherString) {
        int length = value.length < anotherString.value.length
                   ? value.length
                   : anotherString.value.length;

        for (int k = 0; k < length; k++) {
            int difference = value[k] - anotherString.value[k];
            if (difference != 0)
                return difference;
        }

        return value.length - anotherString.value.length;
    }

    public int compareToIgnoreCase(String str) {
        int length = value.length < str.value.length
                   ? value.length
                   : str.value.length;

        for (int k = 0; k < length; k++) {
            char a = Character.toLowerCase(Character.toUpperCase(value[k]));
            char b = Character.toLowerCase(Character.toUpperCase(str.value[k]));
            int difference = a - b;
            if (difference != 0)
                return difference;
        }

        return value.length - str.value.length;
    }

    public String concat(String str) {
        if (str.value.length == 0)
            return this;
        if (value.length == 0)
            return str;
        int length_a = value.length;
        int length_b = str.value.length;
        char[] newValue = new char[length_a + length_b];
        for (int i = 0; i < length_a; i++) {
            newValue[i] = value[i];
        }
        for (int i = 0; i < length_b; i++) {
            newValue[length_a + i] = str.value[i];
        }
        return new String(newValue);
    }

    public boolean contains(CharSequence s) {
        return indexOf(s.toString()) != -1;
    }

    public boolean contentEquals(CharSequence cs) {
        return equals(cs.toString());
    }

    public static String copyValueOf(char[] data) {
        return new String(data);
    }

    public static String copyValueOf(char[] data,
                                     int offset,
                                     int count) {
        return new String(data, offset, count);
    }

    public boolean endsWith(String suffix) {
        int fromIndex = value.length - suffix.value.length;
        return regionMatches(false, fromIndex, suffix, 0, suffix.value.length);
    }

    public boolean equals(Object anObject) {
        if (anObject == null)
            return false;
        if (!(anObject instanceof String))
            return false;
        String str = (String)anObject;
        if (value == str.value)
            return true;
        if (value.length != str.value.length)
            return false;
        for (int i = 0; i < value.length; i++) {
            if (value[i] != str.value[i])
                return false;
        }
        return true;
    }

    public boolean equalsIgnoreCase(String anotherString) {
        if (anotherString == null)
            return false;
        if (value == anotherString.value)
            return true;
        if (value.length != anotherString.value.length)
            return false;
        for (int i = 0; i < value.length; i++) {
            char a = Character.toLowerCase(Character.toUpperCase(value[i]));
            char b = Character.toLowerCase(Character.toUpperCase(anotherString.value[i]));
            if (a != b)
                return false;
        }
        return true;
    }

    public byte[] getBytes() {
        byte[] bytes = new byte[value.length];
        for (int i = 0; i < value.length; i++) {
            bytes[i] = (byte)value[i];
        }
        return bytes;
    }

    public void getChars(int srcBegin,
                         int srcEnd,
                         char[] dst,
                         int dstBegin) {
        if (srcBegin < 0 || srcBegin > srcEnd || srcEnd > value.length ||
            dstBegin < 0 || (dstBegin + (srcEnd - srcBegin)) > dst.length)
            throw new IndexOutOfBoundsException();
        for (int i = 0; i < srcEnd - srcBegin; i++) {
            dst[dstBegin + i] = value[srcBegin + i];
        }
    }

    public int hashCode() {
        int code = 0;
        for (int i = 0; i < value.length; i++) {
            code = code * 31 + value[i];
        }
        return code;
    }

    public int indexOf(int ch) {
        return indexOf(ch, 0);
    }

    public int indexOf(int ch, int fromIndex) {
        if (ch > 0xffff)
            return -1;
        if (fromIndex < 0)
            fromIndex = 0;
        while (fromIndex < value.length) {
            if (value[fromIndex] == ch)
                return fromIndex;
            fromIndex += 1;
        }
        return -1;
    }

    public int indexOf(String str) {
        return indexOf(str, 0);
    }

    public int indexOf(String str, int fromIndex) {
        if (fromIndex < 0)
            fromIndex = 0;
        int maxIndex = value.length - str.value.length;
        while (fromIndex <= maxIndex) {
            if (regionMatches(false, fromIndex, str, 0, str.value.length))
                return fromIndex;
            fromIndex += 1;
        }
        return -1;
    }

    public boolean isEmpty() {
        return value.length == 0;
    }

    public int lastIndexOf(int ch) {
        return lastIndexOf(ch, value.length - 1);
    }

    public int lastIndexOf(int ch, int fromIndex) {
        if (ch > 0xffff)
            return -1;
        if (fromIndex >= value.length)
            fromIndex = value.length - 1;
        while (fromIndex >= 0) {
            if (value[fromIndex] == ch)
                return fromIndex;
            fromIndex -= 1;
        }
        return -1;
    }

    public int lastIndexOf(String str) {
        return indexOf(str, value.length - 1);
    }

    public int lastIndexOf(String str, int fromIndex) {
        if (fromIndex >= value.length)
            fromIndex = value.length - 1;
        while (fromIndex >= 0) {
            if (regionMatches(false, fromIndex, str, 0, str.value.length))
                return fromIndex;
            fromIndex -= 1;
        }
        return -1;
    }

    public int length() {
        return value.length;
    }

    public boolean regionMatches(boolean ignoreCase,
                                 int toffset,
                                 String other,
                                 int ooffset,
                                 int len) {
        if (toffset < 0 || ooffset < 0 || toffset + len > value.length || ooffset + len > other.value.length)
            return false;

        while (len > 0) {
            len -= 1;
            char a = value[toffset];
            toffset += 1;
            char b = other.value[ooffset];
            ooffset += 1;

            if (a != b) {
                if (!ignoreCase)
                    return false;
                char a1 = Character.toLowerCase(Character.toUpperCase(a));
                char b1 = Character.toLowerCase(Character.toUpperCase(b));
                if (a1 != b1)
                    return false;
            }
        }
        return true;
    }

    public boolean regionMatches(int toffset,
                                 String other,
                                 int ooffset,
                                 int len) {
        return regionMatches(false, toffset, other, ooffset, len);
    }

    public String replace(char oldChar, char newChar) {
        boolean replaced = false;
        char[] newValue = new char[value.length];
        for (int i = 0; i < value.length; i++) {
            if (value[i] == oldChar) {
                replaced = true;
                newValue[i] = newChar;
            } else {
                newValue[i] = value[i];
            }
        }
        if (replaced)
            return new String(newValue);
        else
            return this;
    }

    public boolean startsWith(String prefix) {
        return regionMatches(false, 0, prefix, 0, prefix.value.length);
    }

    public boolean startsWith(String prefix, int toffset) {
        return regionMatches(false, toffset, prefix, 0, prefix.value.length);
    }

    public CharSequence subSequence(int beginIndex, int endIndex) {
        return substring(beginIndex, endIndex);
    }

    public String substring(int beginIndex) {
        return substring(beginIndex, value.length);
    }

    public String substring(int beginIndex, int endIndex) {
        if (beginIndex < 0 || endIndex > value.length || beginIndex > endIndex)
            throw new IndexOutOfBoundsException();
        int length = endIndex - beginIndex;
        return new String(value, beginIndex, length);
    }

    public char[] toCharArray() {
        char[] array = new char[value.length];
        for (int i = 0; i < value.length; i++) {
            array[i] = value[i];
        }
        return array;
    }

    public String toLowerCase() {
        char[] newValue = new char[value.length];
        for (int i = 0; i < value.length; i++) {
            newValue[i] = Character.toLowerCase(value[i]);
        }
        return new String(newValue);
    }

    public String toString() {
        return this;
    }

    public String toUpperCase() {
        char[] newValue = new char[value.length];
        for (int i = 0; i < value.length; i++) {
            newValue[i] = Character.toUpperCase(value[i]);
        }
        return new String(newValue);
    }

    public String trim() {
        if (value.length == 0 || (value[0] > '\u0020' && value[value.length - 1] > '\u0020'))
            return this;

        int k = 0;
        while (k < value.length - 1) {
            if (value[k] > '\u0020')
                break;
            k += 1;
        }
        int m = value.length - 1;
        while (m >= 0) {
            if (value[m] > '\u0020')
                break;
            m -= 1;
        }
        return substring(k, m + 1);
    }

    public static String valueOf(boolean b) {
        return b ? "true" : "false";
    }

    public static String valueOf(char c) {
        return new String(new char[] { c });
    }

    public static String valueOf(char[] data) {
        return new String(data, 0, data.length);
    }

    public static String valueOf(char[] data,
                                 int offset,
                                 int count) {
        return new String(data, offset, count);
    }

    public static String valueOf(double d) {
        return Double.toString(d);
    }

    public static String valueOf(float f) {
        return Float.toString(f);
    }

    public static String valueOf(int i) {
        return Integer.toString(i);
    }

    public static String valueOf(long l) {
        return Long.toString(l);
    }

    public static String valueOf(Object obj) {
        return (obj == null) ? "null" : obj.toString();
    }
}
