package p;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.IOException;

import filesystem.iso9660.PrimaryVolumeDescriptor;

class ISOParser {
    public static void main(String[] args) throws IOException {
        byte[] buf = Files.readAllBytes(Paths.get("test.iso"));

        for (int i = PrimaryVolumeDescriptor.STANDARD_IDENTIFIER_START; i <= PrimaryVolumeDescriptor.STANDARD_IDENTIFIER_END; i++) {
            System.out.print(buf[i]);
        }
        System.out.println();

    }
}
