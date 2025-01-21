package java.nio;

import jvm.internal.Memory;

public class ByteBuffer
    extends Buffer
    implements Comparable<ByteBuffer> {

    private boolean bigEndian;

    protected ByteBuffer(int address, int position, int limit, int capacity, boolean bigEndian) {
        super(address, position, limit, capacity);
        bigEndian = bigEndian;
    }

    public static ByteBuffer allocateDirect(int capacity) {
        int address = Memory.allocate(capacity);
        return new ByteBuffer(address, 0, capacity, capacity, true);
    }

    public final byte[] array() {
        throw new UnsupportedOperationException();
    }

    public final int arrayOffset() {
        throw new UnsupportedOperationException();
    }

    private static int mismatch(ByteBuffer a,
                                ByteBuffer b)
    {
        int remA = a.limit - a.position;
        int remB = b.limit - b.position;
        int length = remA > remB ? remB : remA;
        int offA = a.position;
        int offB = b.position;
        for (int i = 0; i < length; i++) {
            if (a.get(offA + i) != b.get(offB + i))
                return i;
        }
        if (remA != remB)
            return length;
        return -1;
    }

    public int compareTo(ByteBuffer that) {
        int pos = mismatch(this, that);
        if (pos >= 0) {
            return this.get(this.position + pos) - that.get(that.position + pos);
        } else {
            int thisRem = this.limit - this.position;
            int thatRem = that.limit - that.position;
            return thisRem - thatRem;
        }
    }

    public boolean equals(Object ob) {
        if (this == ob)
            return true;
        if (!(ob instanceof ByteBuffer))
            return false;
        ByteBuffer other = (ByteBuffer)ob;
        int pos = ByteBuffer.mismatch(this, other);
        return pos == -1;
    }

    public byte get() {
        if (position >= limit)
            throw new IndexOutOfBoundsException();
        byte b = Memory.getU1(address + position);
        position += 1;
        return b;
    }

    public ByteBuffer get(byte[] dst) {
        return get(dst, 0, dst.length);
    }

    public ByteBuffer get(byte[] dst,
                          int offset,
                          int length) {
        int rem = limit - position;
        if (rem < length) {
            throw new BufferUnderflowException();
        }
        if (offset < 0 || offset > dst.length || length < 0 || length > (dst.length - offset)) {
            throw new IndexOutOfBoundsException();
        }
        for (int i = offset; i < offset + length; i++)
            dst[i] = get();

        return this;
    }

    public byte get(int index) {
        if (index < 0 || index > limit)
            throw new IndexOutOfBoundsException();
        return Memory.getU1(address + index);
    }

    public float getFloat() {
        if (limit - position < 4)
            throw new BufferUnderflowException();
        float f = Memory.getUnalignedF4(address + position, bigEndian);
        position += 4;
        return f;
    }

    public float getFloat(int index) {
        if (index < 0 || index >= (limit - 3))
            throw new IndexOutOfBoundsException();
        float f = Memory.getUnalignedF4(address + index, bigEndian);
        return f;
    }

    public int getInt() {
        if (limit - position < 4)
            throw new BufferUnderflowException();
        int i = Memory.getUnalignedU4(address + position, bigEndian);
        position += 4;
        return i;
    }

    public int getInt(int index) {
        if (index < 0 || index >= (limit - 3))
            throw new IndexOutOfBoundsException();
        int i = Memory.getUnalignedU4(address + index, bigEndian);
        return i;
    }

    public short getShort() {
        if (limit - position < 2)
            throw new BufferUnderflowException();
        short i = Memory.getUnalignedU2(address + position, bigEndian);
        position += 4;
        return i;
    }

    public short getShort(short index) {
        if (index < 0 || index >= (limit - 1))
            throw new IndexOutOfBoundsException();
        short i = Memory.getUnalignedU2(address + index, bigEndian);
        return i;
    }

    public final boolean hasArray() {
        return false;
    }

    public int hashCode() {
        int h = 1;
        int limit = this.limit;
        for (int i = position; i < limit; i++) {
            h = 31 * h + (int)get(i);
        }
        return h;
    }

    public boolean isDirect() {
        return true;
    }

    public ByteOrder order() {
        return bigEndian ? ByteOrder.BIG_ENDIAN : ByteOrder.LITTLE_ENDIAN;
    }

    public ByteBuffer order(ByteOrder bo) {
        bigEndian = (bo == ByteOrder.BIG_ENDIAN);
        return this;
    }

    public ByteBuffer put(byte b) {
        if (position >= limit)
            throw new IndexOutOfBoundsException();
        Memory.putU1(address + position, b);
        position += 1;
        return this;
    }

    public final ByteBuffer put(byte[] src) {
        return put(src, 0, src.length);
    }

    public ByteBuffer put(byte[] src,
                          int offset,
                          int length) {
        int rem = limit - position;
        if (rem < length) {
            throw new BufferUnderflowException();
        }
        if (offset < 0 || offset > src.length || length < 0 || length > (src.length - offset)) {
            throw new IndexOutOfBoundsException();
        }
        for (int i = offset; i < offset + length; i++)
            put(src[i]);
        return this;
    }

    public ByteBuffer put(ByteBuffer src) {
        int rem = limit - position;
        int srcRem = src.limit - src.position;
        if (rem < srcRem) {
            throw new BufferUnderflowException();
        }
        if (src == this) {
            throw new IllegalArgumentException();
        }
        for (int i = src.position; i < src.limit; i++) {
            put(src.get(i));
        }
        return this;
    }

    public ByteBuffer put(int index,
                          byte b) {
        if (index < 0 || index > limit)
            throw new IndexOutOfBoundsException();
        Memory.putU1(address + index, b);
        return this;
    }

    public ByteBuffer putFloat(float value) {
        if (limit - position < 4)
            throw new BufferUnderflowException();
        Memory.putUnalignedF4(address + position, value, bigEndian);
        position += 4;
        return this;
    }

    public ByteBuffer putFloat(int index,
                               float value) {
        if (index < 0 || index >= (limit - 3))
            throw new IndexOutOfBoundsException();
        Memory.putUnalignedF4(address + index, value, bigEndian);
        return this;
    }

    public ByteBuffer putInt(int value) {
        if (limit - position < 4)
            throw new BufferUnderflowException();
        Memory.putUnalignedU4(address + position, value, bigEndian);
        position += 4;
        return this;
    }

    public ByteBuffer putInt(int index,
                             int value) {
        if (index < 0 || index >= (limit - 3))
            throw new IndexOutOfBoundsException();
        Memory.putUnalignedU4(address + index, value, bigEndian);
        return this;
    }

    public ByteBuffer putShort(short value) {
        if (limit - position < 4)
            throw new BufferUnderflowException();
        Memory.putUnalignedU2(address + position, value, bigEndian);
        position += 4;
        return this;
    }

    public ByteBuffer putShort(int index,
                               short value) {
        if (index < 0 || index >= (limit - 1))
            throw new IndexOutOfBoundsException();
        Memory.putUnalignedU2(address + index, value, bigEndian);
        return this;
    }

    public ByteBuffer slice() {
        return new ByteBuffer(address,
                              position,
                              limit,
                              capacity,
                              bigEndian);
    }

    public String toString() {
        return getClass().getName()
            + "[pos=" + Integer.toString(position)
            + " lim=" + Integer.toString(limit)
            + " cap=" + Integer.toString(capacity)
            + "]";
    }

    public static ByteBuffer wrap(byte[] array) {
        throw new UnsupportedOperationException();
    }

    public static ByteBuffer wrap(byte[] array,
                                  int offset,
                                  int length) {
        throw new UnsupportedOperationException();
    }
}
