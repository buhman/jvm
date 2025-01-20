package java.nio.file;

import java.io.IOException;
import java.io.InputStream;

public final class Files {


    public static InputStream newInputStream(Path path,
                                             OpenOption... options)
        throws IOException {

        return path.getFileSystem().provider().newInputStream(path, options);
    }
}
