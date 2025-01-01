package filesystem.iso9660;

interface ExtentReader {
    public abstract void readInto(byte[] buf, int extent);
}
