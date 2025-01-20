package jvm.internal;

import java.nio.file.Path;
import java.nio.file.OpenOption;
import java.nio.file.FileSystem;
import java.nio.file.spi.FileSystemProvider;
import java.io.InputStream;
import java.io.IOException;

public class LibcFileSystemProvider extends FileSystemProvider {
    private static LibcFileSystemProvider libcFileSystemProvider = new LibcFileSystemProvider();

    private LibcFileSystemProvider() {
        super();
    }

    public static LibcFileSystemProvider getLibcFileSystemProvider() {
        return libcFileSystemProvider;
    }

    public InputStream newInputStream(Path path,
                                      OpenOption... options)
        throws IOException {
        return new LibcInputStream((LibcPath)path);
    }
}
