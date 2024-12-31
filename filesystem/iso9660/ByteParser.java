package filesystem.iso9660;

public class ByteParser {
    byte[] array;
    public int offset;

    public ByteParser(byte[] array, int offset) {
        this.array = array;
        this.offset = offset;
    }

    public static int shortLE(int i0, int i1) {
        return ((i1 << 8)
              | (i0 << 0)) & 0xffff;
    }

    public static int intLE(int i0, int i1, int i2, int i3) {
        return ((i3 << 24)
              | (i2 << 16)
              | (i1 << 8)
              | (i0 << 0));
    }

    public int getByte(int pos) {
        int i0 = array[offset + pos] & 0xff;
        return i0;
    }

    public int getShortLE(int pos) {
        int i0 = array[offset + pos + 0] & 0xff;
        int i1 = array[offset + pos + 1] & 0xff;

        return shortLE(i0, i1);
    }

    public int getIntLE(int pos) {
        int i0 = array[offset + pos + 0] & 0xff;
        int i1 = array[offset + pos + 1] & 0xff;
        int i2 = array[offset + pos + 2] & 0xff;
        int i3 = array[offset + pos + 3] & 0xff;

        return intLE(i0, i1, i2, i3);
    }
}
