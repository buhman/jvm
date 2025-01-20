package jvm.internal;

import java.nio.file.FileSystem;
import java.nio.file.Path;
import java.nio.file.spi.FileSystemProvider;

public class LibcFileSystem extends FileSystem {
    private static final String separator = "/";

    private static LibcFileSystem libcFileSystem = new LibcFileSystem();

    public static LibcFileSystem getLibcFileSystem() {
        return libcFileSystem;
    }

    private LibcFileSystem() {
        super();
    }

    public void close() {
        // do nothing
    }

    public Path getPath(String first, String ... more) {
        return LibcPath.fromString(first, more);
    }

    public String getSeparator() {
        return LibcFileSystem.separator;
    }

    public boolean isOpen() {
        return true;
    }

    public boolean isReadOnly() {
        return false;
    }

    public FileSystemProvider provider() {
        return LibcFileSystemProvider.getLibcFileSystemProvider();
    }
}
