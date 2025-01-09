package java.nio;

class Buffer {
    protected int mark = -1;
    protected int position = 0;
    protected int limit;
    protected final int capacity;

    Buffer(int mark, int position, int limit, int capacity) {
        this.mark = mark;
        this.position = position;
        this.limit = limit;
        this.capacity = capacity;
    }

    public final int position() {
        return position;
    }

    public final int limit() {
        return limit;
    }

    public final int capacity() {
        return capacity;
    }

    public Buffer limit(int limit) {
        this.limit = limit;
        if (position > limit) position = limit;
        if (mark > limit) mark = -1;
        return this;
    }

    public final boolean hasRemaining() {
        return position < limit;
    }
}
