package java.nio.file;

import jvm.internal.LibcFileSystem;

public final class FileSystems {
    private FileSystems() {
    }

    public static FileSystem getDefault() {
        return LibcFileSystem.getLibcFileSystem();
    }
}
