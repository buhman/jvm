package sega.dreamcast.gdrom;


public class GdromCommandPacketFormat {
    public static class test_unit implements GdromCommandPacketInterface {
        public int command_code;
        public test_unit() {
            this.command_code = 0x0;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                default: return 0;
            }
        }
    }
    public static class req_stat implements GdromCommandPacketInterface {
        public int command_code;
        public int starting_address;
        public int allocation_length;
        public req_stat(int starting_address,
                        int allocation_length
                        ) {
            this.command_code = 0x10;
            this.starting_address = starting_address;
            this.allocation_length = allocation_length;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 2: return starting_address;
                case 4: return allocation_length;
                default: return 0;
            }
        }
    }
    public static class req_mode implements GdromCommandPacketInterface {
        public int command_code;
        public int starting_address;
        public int allocation_length;
        public req_mode(int starting_address,
                        int allocation_length
                        ) {
            this.command_code = 0x11;
            this.starting_address = starting_address;
            this.allocation_length = allocation_length;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 2: return starting_address;
                case 4: return allocation_length;
                default: return 0;
            }
        }
    }
    public static class set_mode implements GdromCommandPacketInterface {
        public int command_code;
        public int starting_address;
        public int allocation_length;
        public set_mode(int starting_address,
                        int allocation_length
                        ) {
            this.command_code = 0x12;
            this.starting_address = starting_address;
            this.allocation_length = allocation_length;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 2: return starting_address;
                case 4: return allocation_length;
                default: return 0;
            }
        }
    }
    public static class req_error implements GdromCommandPacketInterface {
        public int command_code;
        public int allocation_length;
        public req_error(int allocation_length
                         ) {
            this.command_code = 0x13;
            this.allocation_length = allocation_length;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 4: return allocation_length;
                default: return 0;
            }
        }
    }
    public static class get_toc implements GdromCommandPacketInterface {
        public int command_code;
        public int select;
        public int allocation_length0;
        public int allocation_length1;
        public get_toc(int select,
                       int allocation_length
                       ) {
            this.command_code = 0x14;
            this.select = select;
            this.allocation_length0 = (allocation_length >> 8) & 0xff;
            this.allocation_length1 = (allocation_length >> 0) & 0xff;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 1: return select;
                case 3: return allocation_length0;
                case 4: return allocation_length1;
                default: return 0;
            }
        }
    }
    public static class req_ses implements GdromCommandPacketInterface {
        public int command_code;
        public int session_number;
        public int allocation_length;
        public req_ses(int session_number,
                       int allocation_length
                       ) {
            this.command_code = 0x15;
            this.session_number = session_number;
            this.allocation_length = allocation_length;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 2: return session_number;
                case 4: return allocation_length;
                default: return 0;
            }
        }
    }
    public static class cd_open implements GdromCommandPacketInterface {
        public int command_code;
        public cd_open() {
            this.command_code = 0x16;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                default: return 0;
            }
        }
    }
    public static class cd_play implements GdromCommandPacketInterface {
        public int command_code;
        public int parameter_type;
        public int starting_point0;
        public int starting_point1;
        public int starting_point2;
        public int repeat_times;
        public int end_point0;
        public int end_point1;
        public int end_point2;
        public cd_play(int parameter_type,
                       int starting_point,
                       int repeat_times,
                       int end_point
                       ) {
            this.command_code = 0x20;
            this.parameter_type = parameter_type;
            this.starting_point0 = (starting_point >> 16) & 0xff;
            this.starting_point1 = (starting_point >> 8) & 0xff;
            this.starting_point2 = (starting_point >> 0) & 0xff;
            this.repeat_times = repeat_times;
            this.end_point0 = (end_point >> 16) & 0xff;
            this.end_point1 = (end_point >> 8) & 0xff;
            this.end_point2 = (end_point >> 0) & 0xff;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 1: return parameter_type;
                case 2: return starting_point0;
                case 3: return starting_point1;
                case 4: return starting_point2;
                case 6: return repeat_times;
                case 8: return end_point0;
                case 9: return end_point1;
                case 10: return end_point2;
                default: return 0;
            }
        }
    }
    public static class cd_seek implements GdromCommandPacketInterface {
        public int command_code;
        public int parameter_type;
        public int seek_point0;
        public int seek_point1;
        public int seek_point2;
        public cd_seek(int parameter_type,
                       int seek_point
                       ) {
            this.command_code = 0x21;
            this.parameter_type = parameter_type;
            this.seek_point0 = (seek_point >> 16) & 0xff;
            this.seek_point1 = (seek_point >> 8) & 0xff;
            this.seek_point2 = (seek_point >> 0) & 0xff;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 1: return parameter_type;
                case 2: return seek_point0;
                case 3: return seek_point1;
                case 4: return seek_point2;
                default: return 0;
            }
        }
    }
    public static class cd_scan implements GdromCommandPacketInterface {
        public int command_code;
        public int direction;
        public int speed;
        public cd_scan(int direction,
                       int speed
                       ) {
            this.command_code = 0x22;
            this.direction = direction;
            this.speed = speed;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 2: return direction;
                case 3: return speed;
                default: return 0;
            }
        }
    }
    public static class cd_read implements GdromCommandPacketInterface {
        public int command_code;
        public int data;
        public int starting_address0;
        public int starting_address1;
        public int starting_address2;
        public int transfer_length0;
        public int transfer_length1;
        public int transfer_length2;
        public cd_read(int data,
                       int starting_address,
                       int transfer_length
                       ) {
            this.command_code = 0x30;
            this.data = data;
            this.starting_address0 = (starting_address >> 16) & 0xff;
            this.starting_address1 = (starting_address >> 8) & 0xff;
            this.starting_address2 = (starting_address >> 0) & 0xff;
            this.transfer_length0 = (transfer_length >> 16) & 0xff;
            this.transfer_length1 = (transfer_length >> 8) & 0xff;
            this.transfer_length2 = (transfer_length >> 0) & 0xff;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 1: return data;
                case 2: return starting_address0;
                case 3: return starting_address1;
                case 4: return starting_address2;
                case 8: return transfer_length0;
                case 9: return transfer_length1;
                case 10: return transfer_length2;
                default: return 0;
            }
        }
    }
    public static class cd_read2 implements GdromCommandPacketInterface {
        public int command_code;
        public int data;
        public int starting_address0;
        public int starting_address1;
        public int starting_address2;
        public int transfer_length0;
        public int transfer_length1;
        public int next_address0;
        public int next_address1;
        public int next_address2;
        public cd_read2(int data,
                        int starting_address,
                        int transfer_length,
                        int next_address
                        ) {
            this.command_code = 0x31;
            this.data = data;
            this.starting_address0 = (starting_address >> 16) & 0xff;
            this.starting_address1 = (starting_address >> 8) & 0xff;
            this.starting_address2 = (starting_address >> 0) & 0xff;
            this.transfer_length0 = (transfer_length >> 8) & 0xff;
            this.transfer_length1 = (transfer_length >> 0) & 0xff;
            this.next_address0 = (next_address >> 16) & 0xff;
            this.next_address1 = (next_address >> 8) & 0xff;
            this.next_address2 = (next_address >> 0) & 0xff;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 1: return data;
                case 2: return starting_address0;
                case 3: return starting_address1;
                case 4: return starting_address2;
                case 6: return transfer_length0;
                case 7: return transfer_length1;
                case 8: return next_address0;
                case 9: return next_address1;
                case 10: return next_address2;
                default: return 0;
            }
        }
    }
    public static class cd_scd implements GdromCommandPacketInterface {
        public int command_code;
        public int data_format;
        public int allocation_length0;
        public int allocation_length1;
        public cd_scd(int data_format,
                      int allocation_length
                      ) {
            this.command_code = 0x40;
            this.data_format = data_format;
            this.allocation_length0 = (allocation_length >> 8) & 0xff;
            this.allocation_length1 = (allocation_length >> 0) & 0xff;
        }
        public int getByte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 1: return data_format;
                case 3: return allocation_length0;
                case 4: return allocation_length1;
                default: return 0;
            }
        }
    }
}
