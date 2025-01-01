package sega.dreamcast.gdrom;

public class GdromBits {
    public static int status__bsy(int n) {
        return (n >> 7) & 1;
    }
    public static int status__drdy(int n) {
        return (n >> 6) & 1;
    }
    public static int status__df(int n) {
        return (n >> 5) & 1;
    }
    public static int status__dsc(int n) {
        return (n >> 4) & 1;
    }
    public static int status__drq(int n) {
        return (n >> 3) & 1;
    }
    public static int status__corr(int n) {
        return (n >> 2) & 1;
    }
    public static int status__check(int n) {
        return (n >> 0) & 1;
    }
    public static int alternate_status__bsy(int n) {
        return (n >> 7) & 1;
    }
    public static int alternate_status__drdy(int n) {
        return (n >> 6) & 1;
    }
    public static int alternate_status__df(int n) {
        return (n >> 5) & 1;
    }
    public static int alternate_status__dsc(int n) {
        return (n >> 4) & 1;
    }
    public static int alternate_status__drq(int n) {
        return (n >> 3) & 1;
    }
    public static int alternate_status__corr(int n) {
        return (n >> 2) & 1;
    }
    public static int alternate_status__check(int n) {
        return (n >> 0) & 1;
    }
    public static final int command__code__soft_reset = 8 << 0;
    public static final int command__code__execute_device_diagnostic = 144 << 0;
    public static final int command__code__nop = 0 << 0;
    public static final int command__code__packet_command = 160 << 0;
    public static final int command__code__identify_device = 161 << 0;
    public static final int command__code__set_features = 239 << 0;
    public static final int device_control__device_control = 8 << 0;
    public static final int device_control__srst = 1 << 2;
    public static final int device_control__nien = 1 << 1;
    public static final int drive_select__drive_select = 10 << 4;
    public static int drive_select__lun(int n) {
        return (n & 15) << 0;
    }
    public static int error__sense_key(int n) {
        return (n >> 4) & 15;
    }
    public static int error__mcr(int n) {
        return (n >> 3) & 1;
    }
    public static int error__abrt(int n) {
        return (n >> 2) & 1;
    }
    public static int error__eomf(int n) {
        return (n >> 1) & 1;
    }
    public static int error__ili(int n) {
        return (n >> 0) & 1;
    }
    public static final int features__dma__disable = 0 << 0;
    public static final int features__dma__enable = 1 << 0;
    public static final int features_ata__set_clear__clear = 0 << 7;
    public static final int features_ata__set_clear__set = 1 << 7;
    public static final int features_ata__command__set_transfer_mode = 3 << 0;
    public static int interrupt_reason__io(int n) {
        return (n >> 1) & 1;
    }
    public static int interrupt_reason__cod(int n) {
        return (n >> 0) & 1;
    }
    public static final int sector_count__transfer_mode__pio_default_transfer_mode = 0 << 0;
    public static final int sector_count__transfer_mode__pio_flow_control_transfer_mode = 8 << 0;
    public static final int sector_count__transfer_mode__single_word_dma_mode = 16 << 0;
    public static final int sector_count__transfer_mode__multi_word_dma_mode = 32 << 0;
    public static int sector_number__disc_format(int n) {
        return (n >> 4) & 15;
    }
    public static int sector_number__status(int n) {
        return (n >> 0) & 15;
    }
    public static final int error_ata__sense_key__no_sense = 0 << 0;
    public static final int error_ata__sense_key__recovered_error = 1 << 0;
    public static final int error_ata__sense_key__not_ready = 2 << 0;
    public static final int error_ata__sense_key__medium_error = 3 << 0;
    public static final int error_ata__sense_key__hardware_error = 4 << 0;
    public static final int error_ata__sense_key__illegal_request = 5 << 0;
    public static final int error_ata__sense_key__unit_attention = 6 << 0;
    public static final int error_ata__sense_key__data_protect = 7 << 0;
    public static final int error_ata__sense_key__aborted_command = 11 << 0;
}
