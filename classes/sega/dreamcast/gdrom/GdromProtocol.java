package sega.dreamcast.gdrom;

import jvm.internal.Memory;
import sega.dreamcast.gdrom.GdromCommandPacketFormat;

public class GdromProtocol {
    static GdromCommandPacketFormat.get_toc get_toc_command;
    static byte[] toc_buf;

    static GdromCommandPacketFormat.cd_read cd_read_command;

    static {
        int single_density_area = 0;
        int maximum_toc_length = 0x0198;
        get_toc_command = new GdromCommandPacketFormat.get_toc(single_density_area,
                                                               maximum_toc_length);

        toc_buf = new byte[maximum_toc_length];

        cd_read_command = new GdromCommandPacketFormat.cd_read(0, 0, 0);
    }

    public static void packetCommand(GdromCommandPacketInterface command, boolean enable_dma) {
        while (true) {
            int status = Memory.getU1(Gdrom.status);
            if ((GdromBits.status__bsy(status) | GdromBits.status__drq(status)) == 0)
                break;
        }

        int features = enable_dma ? GdromBits.features__dma__enable : GdromBits.features__dma__disable;
        Memory.putU1(Gdrom.features, (byte)features);

        int drive_select = GdromBits.drive_select__drive_select
                         | GdromBits.drive_select__lun(0);
        Memory.putU1(Gdrom.drive_select, (byte)drive_select);

        Memory.putU1(Gdrom.command, (byte)GdromBits.command__code__packet_command);

        //System.out.println("words:");
        for (int i = 0; i < 6; i++) {
            int i0 = command.getByte(i * 2);
            int i1 = command.getByte(i * 2 + 1);
            // little endian
            int word = ((i1 & 0xff) << 8) | (i0 & 0xff);
            Memory.putU2(Gdrom.data, (short)word);
        }

        /*
        while (true) {
            int status = Memory.getU1(Gdrom.status);
            if (GdromBits.status__bsy(status) == 0)
                break;
        }
        */
    }

    public static void readData(byte[] buf, int length) {
        for (int i = 0; i < (length >> 1); i++) {
            int data = Memory.getU2(Gdrom.data);
            buf[i * 2] = (byte)(data);
            buf[i * 2 + 1] = (byte)(data >> 8);
        }
    }

    public static int getFad(byte[] buf, int i) {
        //int i0 = ((int)buf[i * 4 + 0]) & 0xff;
        int i1 = ((int)buf[i * 4 + 1]) & 0xff;
        int i2 = ((int)buf[i * 4 + 2]) & 0xff;
        int i3 = ((int)buf[i * 4 + 3]) & 0xff;

        return (i1 << 16) | (i2 << 8) | (i3 << 0);
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

    // transfer_length is in sectors
    public static void cdReadPIO(byte[] buf, int starting_address, int transfer_length) {
        int data_select = 0b0010; // data
        int expected_data_type = 0b100; // XA mode 2 form 1
        int parameter_type = 0b0; // FAD specified
        int data = (data_select << 4) | (expected_data_type << 1) | (parameter_type);

        cdReadSet(data, starting_address, transfer_length);
        packetCommand(cd_read_command, false); // PIO mode

        int length = 0;

        System.out.println("cdReadPIO");

        while (true) {
            int status = Memory.getU1(Gdrom.status);
            if (GdromBits.status__drq(status) == 0)
                break;

            int low = Memory.getU1(Gdrom.byte_count_low);
            int high = Memory.getU1(Gdrom.byte_count_high);
            int byte_count = ((high & 0xff) << 8) | (low & 0xff);

            readData(buf, byte_count);
            length += byte_count;
        }

        int status = Memory.getU1(Gdrom.status);
        System.out.print("status: ");
        System.out.println(status);

        System.out.print("read length: ");
        System.out.println(length);
    }

    // transfer_length is in sectors
    public static void cdReadDMA(int starting_address, int transfer_length) {
        int data_select = 0b0010; // data
        int expected_data_type = 0b100; // XA mode 2 form 1
        int parameter_type = 0b0; // FAD specified
        int data = (data_select << 4) | (expected_data_type << 1) | (parameter_type);

        System.out.print("cdReadDMA: extent: ");
        System.out.print(starting_address);
        System.out.print(" transfer length (sectors): ");
        System.out.println(transfer_length);

        System.out.println("cdReadSet");
        cdReadSet(data, starting_address, transfer_length);
        System.out.println("packetCommand");
        packetCommand(cd_read_command, true); // DMA mode

        int status = Memory.getU1(Gdrom.status);
        System.out.print("status: ");
        System.out.println(status);
    }
}
