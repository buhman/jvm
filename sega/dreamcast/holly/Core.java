package sega.dreamcast.holly;

import sega.dreamcast.holly.Holly;
import sega.dreamcast.holly.CoreBits;
import java.misc.Memory;

public class Core {
    private Core() {
    }

    public static void init() {
        int fpu_cull_val = 0x3f800000; // 1.0f

        int fpu_perp_val = 0; // 0.0f

        int fpu_param_cfg = CoreBits.fpu_param_cfg__region_header_type__type_2
                          | CoreBits.fpu_param_cfg__tsp_parameter_burst_threshold(31)
		          | CoreBits.fpu_param_cfg__isp_parameter_burst_threshold(31)
		          | CoreBits.fpu_param_cfg__pointer_burst_size(15)
		          | CoreBits.fpu_param_cfg__pointer_first_burst_size(7);

        int half_offset = CoreBits.half_offset__tsp_texel_sampling_position__center
		        | CoreBits.half_offset__tsp_pixel_sampling_position__center
		        | CoreBits.half_offset__fpu_pixel_sampling_position__center;

        int isp_feed_cfg = CoreBits.isp_feed_cfg__cache_size_for_translucency(0x200)
                         | CoreBits.isp_feed_cfg__punch_through_chunk_size(0x040);

        int span_sort_cfg = CoreBits.span_sort_cfg__span_sort_enable
                          | CoreBits.span_sort_cfg__offset_sort_enable;

        int softreset = CoreBits.softreset__pipeline_soft_reset
                      | CoreBits.softreset__ta_soft_reset;

        Memory.putU4(Holly.FPU_CULL_VAL, fpu_cull_val);
        Memory.putU4(Holly.FPU_PERP_VAL, fpu_perp_val);
        Memory.putU4(Holly.FPU_PARAM_CFG, fpu_param_cfg);
        Memory.putU4(Holly.HALF_OFFSET, half_offset);
        Memory.putU4(Holly.ISP_FEED_CFG, isp_feed_cfg);
        Memory.putU4(Holly.SPAN_SORT_CFG, span_sort_cfg);

        Memory.putU4(Holly.SOFTRESET, softreset);
        Memory.putU4(Holly.SOFTRESET, 0);
    }

    public static void fb_init(int x_size, int y_size) {
        int y_coeff = CoreBits.y_coeff__coefficient_1(0x80)
                    | CoreBits.y_coeff__coefficient_0_2(0x40);

        // in 6.10 fixed point; 0x0400 is 1x vertical scale
        int scaler_ctl = CoreBits.scaler_ctl__vertical_scale_factor(0x0400);

        int fb_burstctrl = CoreBits.fb_burstctrl__wr_burst(0x09)
                         | CoreBits.fb_burstctrl__vid_lat(0x3f)
                         | CoreBits.fb_burstctrl__vid_burst(0x39);

        int fb_x_clip = CoreBits.fb_x_clip__fb_x_clip_max(x_size - 1)
                      | CoreBits.fb_x_clip__fb_x_clip_min(0);

        int fb_y_clip = CoreBits.fb_y_clip__fb_y_clip_max(y_size - 1)
                      | CoreBits.fb_y_clip__fb_y_clip_min(0);

        int fb_r_size = CoreBits.fb_r_size__fb_modulus(1)
                      | CoreBits.fb_r_size__fb_y_size(y_size - 3)
                      | CoreBits.fb_r_size__fb_x_size((x_size * 16) / 32 - 1);

        int fb_w_ctrl = CoreBits.fb_w_ctrl__fb_dither
                      | CoreBits.fb_w_ctrl__fb_packmode__565_rgb_16bit;

        Memory.putU4(Holly.Y_COEFF, y_coeff);
        Memory.putU4(Holly.SCALER_CTL, scaler_ctl);
        Memory.putU4(Holly.FB_BURSTCTRL, fb_burstctrl);
        Memory.putU4(Holly.FB_X_CLIP, fb_x_clip);
        Memory.putU4(Holly.FB_Y_CLIP, fb_y_clip);
        Memory.putU4(Holly.FB_R_SIZE, fb_r_size);
        Memory.putU4(Holly.FB_W_CTRL, fb_w_ctrl);
    }

    public static void fb_r_disable() {
        Memory.putU4(Holly.FB_R_CTRL, 0);
    }

    public static void fb_r_enable() {
        int fb_r_ctrl =
              CoreBits.fb_r_ctrl__vclk_div__pclk_vclk_1
            | CoreBits.fb_r_ctrl__fb_depth__565_rgb_16bit
            | CoreBits.fb_r_ctrl__fb_enable;

        Memory.putU4(Holly.FB_R_CTRL, fb_r_ctrl);
    }

    public static void start_render(int region_array_start,
                                    int isp_tsp_parameters_start,
                                    int background_start,
                                    int frame_address,    // in pixels
                                    int frame_width      // in pixels
                                    )
    {
        int background_offset = background_start - isp_tsp_parameters_start;

        int isp_backgnd_t = CoreBits.isp_backgnd_t__tag_address(background_offset / 4)
                          | CoreBits.isp_backgnd_t__tag_offset(0)
                          | CoreBits.isp_backgnd_t__skip(1);

        int isp_backgnd_d = 0x37c00000; // 0.00002

        int bytes_per_pixel = 2;
        int fb_w_linestride = (frame_width * bytes_per_pixel) >> 3;

        Memory.putU4(Holly.ISP_BACKGND_T, isp_backgnd_t);
        Memory.putU4(Holly.ISP_BACKGND_D, isp_backgnd_d);

        Memory.putU4(Holly.REGION_BASE, region_array_start);
        Memory.putU4(Holly.PARAM_BASE, isp_tsp_parameters_start);

        Memory.putU4(Holly.FB_W_LINESTRIDE, fb_w_linestride);
        Memory.putU4(Holly.FB_W_SOF1, frame_address);

        Memory.putU4(Holly.STARTRENDER, 1);
    }

    public static void wait_end_of_render_tsp() {
        int istnrm__end_of_render_tsp = 1 << 2;
        while ((Memory.getU4(0xa05f6900) & istnrm__end_of_render_tsp) == 0) {
            int isterr = Memory.getU4(0xa05f6908);
            if (isterr != 0) {
                System.out.print("isterr:");
                System.out.println(isterr);
                Memory.putU4(Holly.SOFTRESET, CoreBits.softreset__pipeline_soft_reset);
                Memory.putU4(Holly.SOFTRESET, 0);
                Memory.putU4(0xa05f6908, isterr);
                break;
            }
        };
        int istnrm = (1 << 2)  // istnrm__end_of_render_tsp
                   | (1 << 1)  // istnrm__end_of_render_isp
                   | (1 << 0); // istnrm__end_of_render_video;
        Memory.putU4(0xa05f6900, istnrm);
    }
}
