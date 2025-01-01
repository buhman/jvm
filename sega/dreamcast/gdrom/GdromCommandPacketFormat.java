package sega.dreamcast.gdrom;


public class GdromCommandPacketFormat {
    public static class test_unit {
        public byte command_code;
        public byte _res0;
        public byte _res1;
        public byte _res2;
        public byte _res3;
        public byte _res4;
        public byte _res5;
        public byte _res6;
        public byte _res7;
        public byte _res8;
        public byte _res9;
        public byte _res10;
        public test_unit() {
            this.command_code = 0x0;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
            this._res7 = 0;
            this._res8 = 0;
            this._res9 = 0;
            this._res10 = 0;
        }
        public get_byte(int ix) {
            switch (ix) {
                case 0: return command_code;
                default: return 0;
            }
        }
    }
    public static class req_stat {
        public byte command_code;
        public byte _res0;
        public byte starting_address;
        public byte _res1;
        public byte allocation_length;
        public byte _res2;
        public byte _res3;
        public byte _res4;
        public byte _res5;
        public byte _res6;
        public byte _res7;
        public byte _res8;
        public req_stat(byte starting_address,
                        byte allocation_length
                        ) {
            this.command_code = 0x10;
            this._res0 = 0;
            this.starting_address = starting_address;
            this._res1 = 0;
            this.allocation_length = allocation_length;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
            this._res7 = 0;
            this._res8 = 0;
        }
        public get_byte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 2: return starting_address;
                case 4: return allocation_length;
                default: return 0;
            }
        }
    }
    public static class req_mode {
        public byte command_code;
        public byte _res0;
        public byte starting_address;
        public byte _res1;
        public byte allocation_length;
        public byte _res2;
        public byte _res3;
        public byte _res4;
        public byte _res5;
        public byte _res6;
        public byte _res7;
        public byte _res8;
        public req_mode(byte starting_address,
                        byte allocation_length
                        ) {
            this.command_code = 0x11;
            this._res0 = 0;
            this.starting_address = starting_address;
            this._res1 = 0;
            this.allocation_length = allocation_length;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
            this._res7 = 0;
            this._res8 = 0;
        }
        public get_byte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 2: return starting_address;
                case 4: return allocation_length;
                default: return 0;
            }
        }
    }
    public static class set_mode {
        public byte command_code;
        public byte _res0;
        public byte starting_address;
        public byte _res1;
        public byte allocation_length;
        public byte _res2;
        public byte _res3;
        public byte _res4;
        public byte _res5;
        public byte _res6;
        public byte _res7;
        public byte _res8;
        public set_mode(byte starting_address,
                        byte allocation_length
                        ) {
            this.command_code = 0x12;
            this._res0 = 0;
            this.starting_address = starting_address;
            this._res1 = 0;
            this.allocation_length = allocation_length;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
            this._res7 = 0;
            this._res8 = 0;
        }
        public get_byte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 2: return starting_address;
                case 4: return allocation_length;
                default: return 0;
            }
        }
    }
    public static class req_error {
        public byte command_code;
        public byte _res0;
        public byte _res1;
        public byte _res2;
        public byte allocation_length;
        public byte _res3;
        public byte _res4;
        public byte _res5;
        public byte _res6;
        public byte _res7;
        public byte _res8;
        public byte _res9;
        public req_error(byte allocation_length
                         ) {
            this.command_code = 0x13;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this.allocation_length = allocation_length;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
            this._res7 = 0;
            this._res8 = 0;
            this._res9 = 0;
        }
        public get_byte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 4: return allocation_length;
                default: return 0;
            }
        }
    }
    public static class get_toc {
        public byte command_code;
        public byte select;
        public byte _res0;
        public byte allocation_length0;
        public byte allocation_length1;
        public byte _res1;
        public byte _res2;
        public byte _res3;
        public byte _res4;
        public byte _res5;
        public byte _res6;
        public byte _res7;
        public get_toc(byte select,
                       int allocation_length
                       ) {
            this.command_code = 0x14;
            this.select = select;
            this._res0 = 0;
            this.allocation_length0 = (allocation_length >> 8) & 0xff;
            this.allocation_length1 = (allocation_length >> 0) & 0xff;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
            this._res7 = 0;
        }
        public get_byte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 1: return select;
                case 3: return allocation_length0;
                case 4: return allocation_length1;
                default: return 0;
            }
        }
    }
    public static class req_ses {
        public byte command_code;
        public byte _res0;
        public byte session_number;
        public byte _res1;
        public byte allocation_length;
        public byte _res2;
        public byte _res3;
        public byte _res4;
        public byte _res5;
        public byte _res6;
        public byte _res7;
        public byte _res8;
        public req_ses(byte session_number,
                       byte allocation_length
                       ) {
            this.command_code = 0x15;
            this._res0 = 0;
            this.session_number = session_number;
            this._res1 = 0;
            this.allocation_length = allocation_length;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
            this._res7 = 0;
            this._res8 = 0;
        }
        public get_byte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 2: return session_number;
                case 4: return allocation_length;
                default: return 0;
            }
        }
    }
    public static class cd_open {
        public byte command_code;
        public byte _res0;
        public byte _res1;
        public byte _res2;
        public byte _res3;
        public byte _res4;
        public byte _res5;
        public byte _res6;
        public byte _res7;
        public byte _res8;
        public byte _res9;
        public byte _res10;
        public cd_open() {
            this.command_code = 0x16;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
            this._res7 = 0;
            this._res8 = 0;
            this._res9 = 0;
            this._res10 = 0;
        }
        public get_byte(int ix) {
            switch (ix) {
                case 0: return command_code;
                default: return 0;
            }
        }
    }
    public static class cd_play {
        public byte command_code;
        public byte parameter_type;
        public byte starting_point0;
        public byte starting_point1;
        public byte starting_point2;
        public byte _res0;
        public byte repeat_times;
        public byte _res1;
        public byte end_point0;
        public byte end_point1;
        public byte end_point2;
        public byte _res2;
        public cd_play(byte parameter_type,
                       int starting_point,
                       byte repeat_times,
                       int end_point
                       ) {
            this.command_code = 0x20;
            this.parameter_type = parameter_type;
            this.starting_point0 = (starting_point >> 16) & 0xff;
            this.starting_point1 = (starting_point >> 8) & 0xff;
            this.starting_point2 = (starting_point >> 0) & 0xff;
            this._res0 = 0;
            this.repeat_times = repeat_times;
            this._res1 = 0;
            this.end_point0 = (end_point >> 16) & 0xff;
            this.end_point1 = (end_point >> 8) & 0xff;
            this.end_point2 = (end_point >> 0) & 0xff;
            this._res2 = 0;
        }
        public get_byte(int ix) {
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
    public static class cd_seek {
        public byte command_code;
        public byte parameter_type;
        public byte seek_point0;
        public byte seek_point1;
        public byte seek_point2;
        public byte _res0;
        public byte _res1;
        public byte _res2;
        public byte _res3;
        public byte _res4;
        public byte _res5;
        public byte _res6;
        public cd_seek(byte parameter_type,
                       int seek_point
                       ) {
            this.command_code = 0x21;
            this.parameter_type = parameter_type;
            this.seek_point0 = (seek_point >> 16) & 0xff;
            this.seek_point1 = (seek_point >> 8) & 0xff;
            this.seek_point2 = (seek_point >> 0) & 0xff;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
        }
        public get_byte(int ix) {
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
    public static class cd_scan {
        public byte command_code;
        public byte _res0;
        public byte direction;
        public byte speed;
        public byte _res1;
        public byte _res2;
        public byte _res3;
        public byte _res4;
        public byte _res5;
        public byte _res6;
        public byte _res7;
        public byte _res8;
        public cd_scan(byte direction,
                       byte speed
                       ) {
            this.command_code = 0x22;
            this._res0 = 0;
            this.direction = direction;
            this.speed = speed;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
            this._res7 = 0;
            this._res8 = 0;
        }
        public get_byte(int ix) {
            switch (ix) {
                case 0: return command_code;
                case 2: return direction;
                case 3: return speed;
                default: return 0;
            }
        }
    }
    public static class cd_read {
        public byte command_code;
        public byte data;
        public byte starting_address0;
        public byte starting_address1;
        public byte starting_address2;
        public byte _res0;
        public byte _res1;
        public byte _res2;
        public byte transfer_length0;
        public byte transfer_length1;
        public byte transfer_length2;
        public byte _res3;
        public cd_read(byte data,
                       int starting_address,
                       int transfer_length
                       ) {
            this.command_code = 0x30;
            this.data = data;
            this.starting_address0 = (starting_address >> 16) & 0xff;
            this.starting_address1 = (starting_address >> 8) & 0xff;
            this.starting_address2 = (starting_address >> 0) & 0xff;
            this._res0 = 0;
            this._res1 = 0;
            this._res2 = 0;
            this.transfer_length0 = (transfer_length >> 16) & 0xff;
            this.transfer_length1 = (transfer_length >> 8) & 0xff;
            this.transfer_length2 = (transfer_length >> 0) & 0xff;
            this._res3 = 0;
        }
        public get_byte(int ix) {
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
    public static class cd_read2 {
        public byte command_code;
        public byte data;
        public byte starting_address0;
        public byte starting_address1;
        public byte starting_address2;
        public byte _res0;
        public byte transfer_length0;
        public byte transfer_length1;
        public byte next_address0;
        public byte next_address1;
        public byte next_address2;
        public byte _res1;
        public cd_read2(byte data,
                        int starting_address,
                        int transfer_length,
                        int next_address
                        ) {
            this.command_code = 0x31;
            this.data = data;
            this.starting_address0 = (starting_address >> 16) & 0xff;
            this.starting_address1 = (starting_address >> 8) & 0xff;
            this.starting_address2 = (starting_address >> 0) & 0xff;
            this._res0 = 0;
            this.transfer_length0 = (transfer_length >> 8) & 0xff;
            this.transfer_length1 = (transfer_length >> 0) & 0xff;
            this.next_address0 = (next_address >> 16) & 0xff;
            this.next_address1 = (next_address >> 8) & 0xff;
            this.next_address2 = (next_address >> 0) & 0xff;
            this._res1 = 0;
        }
        public get_byte(int ix) {
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
    public static class cd_scd {
        public byte command_code;
        public byte data_format;
        public byte _res0;
        public byte allocation_length0;
        public byte allocation_length1;
        public byte _res1;
        public byte _res2;
        public byte _res3;
        public byte _res4;
        public byte _res5;
        public byte _res6;
        public byte _res7;
        public cd_scd(byte data_format,
                      int allocation_length
                      ) {
            this.command_code = 0x40;
            this.data_format = data_format;
            this._res0 = 0;
            this.allocation_length0 = (allocation_length >> 8) & 0xff;
            this.allocation_length1 = (allocation_length >> 0) & 0xff;
            this._res1 = 0;
            this._res2 = 0;
            this._res3 = 0;
            this._res4 = 0;
            this._res5 = 0;
            this._res6 = 0;
            this._res7 = 0;
        }
        public get_byte(int ix) {
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
