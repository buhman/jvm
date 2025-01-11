package java.lang;

public class StringBuilder {
    String[] strings;
    int count;

    public StringBuilder() {
        strings = new String[0];
    }

    public StringBuilder(int capacity) {
        strings = new String[capacity];
    }

    private void ensureCapacityInternal(int minimumCapacity) {
        if (strings.length < minimumCapacity) {
            String[] new_strings = new String[minimumCapacity + 3];
            for (int i = 0; i < count; i++) {
                new_strings[i] = strings[i];
            }
            strings = new_strings;
        }
    }

    public StringBuilder append(String s) {
        ensureCapacityInternal(count + 1);
        strings[count] = s;
        count += 1;
        return this;
    }

    public String toString() {
        int size = 0;
        for (int i = 0; i < count; i++) {
            size += strings[i].length();
        }
        byte[] buf = new byte[size];
        int ix = 0;
        for (int i = 0; i < count; i++) {
            byte[] src = strings[i].getBytes();
            for (int j = 0; j < src.length; j++) {
                buf[ix] = src[j];
                ix += 1;
            }
        }
        return new String(buf);
    }
}
