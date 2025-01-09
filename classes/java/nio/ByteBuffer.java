package java.nio;

public class ByteBuffer extends Buffer {
    private int offset;
    private boolean bigEndian;
    //private boolean sameEndian;

    private byte[] array;

    private ByteBuffer(byte[] array, int offset, int length) {
        super(-1, 0, length, length);
        this.array = array;
        this.order(ByteOrder.BIG_ENDIAN);
    }

    public static ByteBuffer wrap(byte[] array) {
        return new ByteBuffer(array, 0, array.length);
    }

    public static ByteBuffer wrap(byte[] array, int offset, int length) {
        return new ByteBuffer(array, offset, length);
    }

    public ByteOrder order() {
        return bigEndian ? ByteOrder.BIG_ENDIAN : ByteOrder.LITTLE_ENDIAN;
    }

    public ByteBuffer order(ByteOrder bo) {
        bigEndian = (bo == ByteOrder.BIG_ENDIAN);
        //sameEndian = (bo == ByteOrder.nativeOrder());
        return this;
    }

    public ByteBuffer offset(int off) {
        offset = off;
        return this;
    }

    private static int intBE(int i0, int i1, int i2, int i3) {
        return ((i0 << 24)
              | (i1 << 16)
              | (i2 << 8)
              | (i3 << 0));
    }

    private static int intLE(int i0, int i1, int i2, int i3) {
        return ((i0 << 0)
              | (i1 << 8)
              | (i2 << 16)
              | (i3 << 24));
    }

    private static int shortBE(int i0, int i1) {
        return ((i0 << 8)
              | (i1 << 0));
    }

    private static int shortLE(int i0, int i1) {
        return ((i0 << 0)
              | (i1 << 8));
    }

    private int ix(int pos) {
        return offset + pos;
    }

    public byte get() {
        byte i0 = array[ix(position)];
        position += 1;
        return i0;
    }

    public byte get(int pos) {
        byte i0 = array[ix(pos)];
        return i0;
    }

    public short getShort() {
        int i0 = array[ix(position) + 0];
        int i1 = array[ix(position) + 1];

        position += 2;

        if (bigEndian) {
            return (short)shortBE(i0, i1);
        } else {
            return (short)shortLE(i0, i1);
        }
    }

    public short getShort(int pos) {
        int i0 = array[ix(pos) + 0];
        int i1 = array[ix(pos) + 1];

        if (bigEndian) {
            return (short)shortBE(i0, i1);
        } else {
            return (short)shortLE(i0, i1);
        }
    }

    public int getInt() {
        int i0 = array[ix(position) + 0];
        int i1 = array[ix(position) + 1];
        int i2 = array[ix(position) + 2];
        int i3 = array[ix(position) + 3];

        position += 4;

        if (bigEndian) {
            return intBE(i0, i1, i2, i3);
        } else {
            return intLE(i0, i1, i2, i3);
        }
    }

    public int getInt(int pos) {
        int i0 = array[ix(pos) + 0];
        int i1 = array[ix(pos) + 1];
        int i2 = array[ix(pos) + 2];
        int i3 = array[ix(pos) + 3];

        if (bigEndian) {
            return intBE(i0, i1, i2, i3);
        } else {
            return intLE(i0, i1, i2, i3);
        }
    }
}
