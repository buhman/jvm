package java.nio.file.spi;

import java.nio.file.Path;
import java.nio.file.OpenOption;
import java.io.InputStream;
import java.io.IOException;

public abstract class FileSystemProvider {
    protected FileSystemProvider() {
    }

    public InputStream newInputStream(Path path,
                                      OpenOption... options)
        throws IOException {

        throw new IOException();
    }
}
