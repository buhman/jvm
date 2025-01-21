package sega.dreamcast.sh7091;

import java.nio.ByteBuffer;

import sega.dreamcast.MemoryMap;

public abstract class StoreQueueBuffer extends ByteBuffer {
    public StoreQueueBuffer() {
        super(MemoryMap.store_queue, 0, 64, 64, true);
    }

    public abstract void submit();
}
