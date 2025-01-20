package java.nio.file;

import java.io.Closeable;
import java.io.IOException;
import java.nio.file.spi.FileSystemProvider;

public abstract class FileSystem
    implements Closeable {

    protected FileSystem() {
    }

    public abstract void close()
        throws IOException;

    public abstract Path getPath(String first,
                                 String... more);

    public abstract String getSeparator();

    public abstract boolean isOpen();

    public abstract boolean isReadOnly();

    public abstract FileSystemProvider provider();
}
