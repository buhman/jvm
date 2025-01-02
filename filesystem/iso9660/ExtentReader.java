package filesystem.iso9660;

public interface ExtentReader {
    public abstract void readInto(byte[] buf, int extent);
}
