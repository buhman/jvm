package filesystem.iso9660;

import filesystem.iso9660.PrimaryVolumeDescriptor;
import filesystem.iso9660.DirectoryRecord;

public class VolumeParser {
    int fad;
    byte[] buf;
    DirectoryRecord dr;
    ExtentReader reader;

    static final int FILE_FLAGS__DIRECTORY = 2;

    public static void printIdentifier(byte[] buf, int offset, int start, int length) {
        for (int i = 0; i < length; i++) {
            System.out.print((char)buf[offset + start + i]);
        }
    }

    public void printStandardIdentifier() {
        System.out.print("standard identifier: ");
        int start = PrimaryVolumeDescriptor.STANDARD_IDENTIFIER_START;
        int end = PrimaryVolumeDescriptor.STANDARD_IDENTIFIER_END;
        for (int i = start; i <= end; i++) {
            System.out.print((char)buf[i]);
        }
        System.out.println();
    }

    public boolean drIsSelfOrParent() {
        if (dr.lengthOfFileIdentifier() != 1) {
            return false;
        }
        byte start = buf[DirectoryRecord.FILE_IDENTIFIER_START];
        return (start == 0 || start == 1);
    }

    public int walkDirectoryRecord(int indent, int[] child_extents, int[] child_lengths, int child_ix) {
        if (drIsSelfOrParent()) {
            return child_ix;
        }

        for (int i = 0; i < indent; i++)
            System.out.print("  ");

        System.out.print("offset: ");
        System.out.print(dr.offset);

        //System.out.print("; file_flags: ");
        //System.out.print((int)dr.fileFlags());

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

        System.out.print(" file_identifier: ");
        printIdentifier(buf, dr.offset, DirectoryRecord.FILE_IDENTIFIER_START, dr.lengthOfFileIdentifier());
        System.out.println();

        return child_ix;
    }


    public void walkDirectory(int extent, int num_extents, int indent) {
        int[] child_extents = new int[64];
        int[] child_lengths = new int[64];
        int child_ix = 0;

        while (num_extents > 0) {
            for (int i = 0; i < indent; i++)
                System.out.print("  ");
            System.out.print("read extent : ");
            System.out.println(extent);
            reader.readInto(buf, extent);
            dr.offset = 0;

            while (true) {
                if (dr.lengthOfDirectoryRecord() == 0) {
                    break;
                }

                child_ix = walkDirectoryRecord(indent, child_extents, child_lengths, child_ix);

                dr.offset += dr.lengthOfDirectoryRecord();
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

    public void parse() {
        int pvd_extent = this.fad + 16;

        System.out.print("pvd_extent: ");
        System.out.println(pvd_extent);
        reader.readInto(buf, pvd_extent);

        printStandardIdentifier();

        dr.offset = PrimaryVolumeDescriptor.DIRECTORY_RECORD_FOR_ROOT_DIRECTORY_START;
        System.out.print("root directory record: location: ");
        System.out.print(dr.locationOfExtent());
        System.out.print(" ; data length: ");
        System.out.println(dr.dataLength());

        int extent = dr.locationOfExtent();
        int num_extents = dr.dataLength() >> 11; // division by 2048
        walkDirectory(extent, num_extents, 0);
    }

    public VolumeParser(int fad, ExtentReader reader) {
        this.fad = fad;
        this.reader = reader;
        this.buf = new byte[2048];
        this.dr = new DirectoryRecord(this.buf, 0);
    }

    /*
    import filesystem.iso9660.TestExtentReader;

    public static void main(String[] args) {
        TestExtentReader reader = new TestExtentReader();
        VolumeParser parser = new VolumeParser(reader);
        parser.parse();
    }
    */
}
