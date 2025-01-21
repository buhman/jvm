package java.nio;

public abstract class Buffer {
    protected final int address;
    protected int position;
    protected int limit;
    protected final int capacity;

    protected Buffer(int address, int position, int limit, int capacity) {
        this.address = address;
        this.position = position;
        this.limit = limit;
        this.capacity = capacity;
    }

    public final int capacity() {
        return capacity;
    }

    public final Buffer clear() {
        position = 0;
        limit = capacity;
        return this;
    }

    public final Buffer flip() {
        limit = position;
        position = 0;
        return this;
    }

    public final boolean hasRemaining() {
        return position < limit;
    }

    public final int limit() {
        return limit;
    }

    public Buffer limit(int newLimit) {
        if (newLimit < 0 || newLimit > capacity)
            throw new IllegalArgumentException();
        this.limit = newLimit;
        if (position > newLimit) position = newLimit;
        return this;
    }

    public final int position() {
        return position;
    }

    public final Buffer position(int newPosition) {
        if (newPosition < 0 || newPosition > limit)
            throw new IllegalArgumentException();
        position = newPosition;
        return this;
    }

    public final int remaining() {
        int elements = limit - position;
        if (elements < 0)
            elements = 0;
        return elements;
    }

    public final Buffer rewind() {
        position = 0;
        return this;
    }
}
