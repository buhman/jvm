package p;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.IOException;

import filesystem.iso9660.PrimaryVolumeDescriptor;
import filesystem.iso9660.DirectoryRecord;

class ISOParser {
    byte[] buf;
    DirectoryRecord dr;

    static final int FILE_FLAGS__DIRECTORY = 2;

    public static void printIdentifier(byte[] buf, int offset, int start, int length) {
        for (int i = 0; i < length; i++) {
            System.out.print((char)buf[offset + start + i]);
        }
    }

    public boolean drIsSelfOrParent() {
        if (dr.lengthOfFileIdentifier() != 1) {
            return false;
        }
        byte start = buf[DirectoryRecord.FILE_IDENTIFIER_START];
        return (start == 0 || start == 1);
    }

    public void walkDirectory(int extent, int num_extents, int indent) {
        int[] child_extents = new int[64];
        int[] child_lengths = new int[64];
        int child_ix = 0;

        while (num_extents > 0) {
            int offset = extent * 2048;
            while (true) {
                dr.offset = offset;
                if (dr.lengthOfDirectoryRecord() == 0) {
                    System.out.print("break\n");
                    break;
                }

                if (!drIsSelfOrParent()) {
                    for (int i = 0; i < indent; i++)
                        System.out.print("  ");

                    System.out.print("offset: ");
                    System.out.print(dr.offset);

                    System.out.print("; file_flags: ");
                    System.out.print((int)dr.fileFlags());

                    if ((dr.fileFlags() & FILE_FLAGS__DIRECTORY) == 0) {
                        System.out.print(" [regular file] ");
                        //dr.locationOfExtent();
                        //dr.dataLength();
                    } else {
                        System.out.print(" [directory] ");
                        child_extents[child_ix] = dr.locationOfExtent();
                        child_lengths[child_ix] = dr.dataLength();
                        child_ix += 1;
                    }

                    System.out.print("; file_identifier: ");
                    printIdentifier(buf, offset, DirectoryRecord.FILE_IDENTIFIER_START, dr.lengthOfFileIdentifier());
                    System.out.println();
                }

                offset += dr.lengthOfDirectoryRecord();
            }
            num_extents -= 1;
            extent += 1;
        }

        for (int i = 0; i < child_ix; i++) {
            int child_extent = child_extents[i];
            int child_num_extents = child_lengths[i] >> 11; // division by 2048
            walkDirectory(child_extent, child_num_extents, indent + 1);
        }
    }

    public static void main(String[] args) throws IOException {
        ISOParser parser = new ISOParser();
        parser.buf = Files.readAllBytes(Paths.get("classes.iso"));

        int pvd_offset = 2048 * 16;

        System.out.print("standard identifier: ");
        for (int i = PrimaryVolumeDescriptor.STANDARD_IDENTIFIER_START; i <= PrimaryVolumeDescriptor.STANDARD_IDENTIFIER_END; i++) {
            System.out.print((char)parser.buf[pvd_offset + i]);
        }
        System.out.println();


        int directory_record_for_root_directory = pvd_offset + PrimaryVolumeDescriptor.DIRECTORY_RECORD_FOR_ROOT_DIRECTORY_START;
        System.out.println("root directory record: ");
        parser.dr = new DirectoryRecord(parser.buf, directory_record_for_root_directory);
        System.out.println(parser.dr.locationOfExtent());
        System.out.println(parser.dr.dataLength());

        int extent = parser.dr.locationOfExtent();
        int num_extents = parser.dr.dataLength() >> 11; // division by 2048
        parser.walkDirectory(extent, num_extents, 0);
    }
}
