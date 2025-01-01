package sega.dreamcast.gdrom;

import java.misc.Memory;
import sega.dreamcast.gdrom.GdromCommandPacketFormat;

public class GdromProtocol {
    static GdromCommandPacketFormat.get_toc get_toc_command;
    static short[] toc_buf;

    static GdromCommandPacketFormat.cd_read cd_read_command;

    static {
        int single_density_area = 0;
        int maximum_toc_length = 0x0198;
        get_toc_command = new GdromCommandPacketFormat.get_toc(single_density_area,
                                                               maximum_toc_length);

        toc_buf = new short[maximum_toc_length >> 1];

        cd_read_command = new GdromCommandPacketFormat.cd_read(0, 0, 0);
    }

    public static void packetCommand(GdromCommandPacketInterface command, boolean enable_dma) {
        while (true) {
            int status = Memory.getU1(Gdrom.status);
            if ((GdromBits.status__bsy(status) | GdromBits.status__drq(status)) == 0)
                break;
        }

        int features = enable_dma ? GdromBits.features__dma__enable : GdromBits.features__dma__disable;
        Memory.putU1(Gdrom.features, features);

        int drive_select = GdromBits.drive_select__drive_select
                         | GdromBits.drive_select__lun(0);
        Memory.putU1(Gdrom.drive_select, drive_select);

        Memory.putU1(Gdrom.command, GdromBits.command__code__packet_command);

        System.out.println("words:");
        for (int i = 0; i < 6; i++) {
            int i0 = command.getByte(i * 2);
            int i1 = command.getByte(i * 2 + 1);
            // little endian
            int word = ((i1 & 0xff) << 8) | (i0 & 0xff);
            System.out.println(word);
            Memory.putU2(Gdrom.data, word);
        }

        while (true) {
            int status = Memory.getU1(Gdrom.status);
            if (GdromBits.status__bsy(status) == 0)
                break;
        }
    }

    public static void readData(short[] buf, int length) {
        for (int i = 0; i < (length >> 1); i++) {
            buf[i] = (short)Memory.getU2(Gdrom.data);
        }
    }

    public static int getFad(short[] buf, int i) {
        int low = toc_buf[i * 2] & 0xffff;
        int high = toc_buf[i * 2 + 1] & 0xffff;
        int i0 = (high >> 8) & 0xff;
        int i1 = high & 0xff;
        int i2 = (low >> 8) & 0xff;
        //int i3 = low & 0xff;

        return (i2 << 16) | (i1 << 8) | i0;
    }

    public static int tocGetDataTrackFad() {
        System.out.println("PacketCommand:");
        packetCommand(get_toc_command, false); // PIO mode

        int low = Memory.getU1(Gdrom.byte_count_low);
        int high = Memory.getU1(Gdrom.byte_count_high);
        int byte_count = ((high & 0xff) << 8) | (low & 0xff);
        System.out.print("byte count:");
        System.out.println(byte_count);

        System.out.println("tracks:");
        readData(toc_buf, byte_count);
        for (int i = 0; i < 99; i++) {
            int fad = getFad(toc_buf, i);
            if (fad == 0xffffff)
                break;
            System.out.print("[");
            System.out.print(i);
            System.out.print("] ");
            System.out.println(fad);
        }

        int status = Memory.getU1(Gdrom.status);
        System.out.print("status: ");
        System.out.println(status);

        // assume track 1 is the correct track
        return getFad(toc_buf, 1);
    }

    public static void cdReadSet(int data, int starting_address, int transfer_length) {
        cd_read_command.data = data;
        cd_read_command.starting_address0 = (starting_address >> 16) & 0xff;
        cd_read_command.starting_address1 = (starting_address >> 8) & 0xff;
        cd_read_command.starting_address2 = (starting_address >> 0) & 0xff;
        cd_read_command.transfer_length0 = (transfer_length >> 16) & 0xff;
        cd_read_command.transfer_length1 = (transfer_length >> 8) & 0xff;
        cd_read_command.transfer_length2 = (transfer_length >> 0) & 0xff;
    }

    public static void cdReadDMA(int starting_address, int transfer_length) {
        int data_select = 0b0010; // data
        int expected_data_type = 0b100; // XA mode 2 form 1
        int parameter_type = 0b0; // FAD specified
        int data = (data_select << 4) | (expected_data_type << 1) | (parameter_type);

        cdReadSet(data, starting_address, transfer_length);
        packetCommand(cd_read_command, true); // DMA mode
    }
}
