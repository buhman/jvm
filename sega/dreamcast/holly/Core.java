package sega.dreamcast.holly;

import sega.dreamcast.holly.Holly;
import sega.dreamcast.holly.CoreBits;
import java.misc.Memory;

public class Core {
    private Core() {
    }

    public static void init() {
        int fb_w_ctrl = CoreBits.fb_w_ctrl__fb_dither
                      | CoreBits.fb_w_ctrl__fb_packmode__565_rgb_16bit;

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

        Memory.putU4(Holly.FB_W_CTRL, fb_w_ctrl);
        Memory.putU4(Holly.FPU_CULL_VAL, fpu_cull_val);
        Memory.putU4(Holly.FPU_PERP_VAL, fpu_perp_val);
        Memory.putU4(Holly.FPU_PARAM_CFG, fpu_param_cfg);
        Memory.putU4(Holly.HALF_OFFSET, half_offset);
        Memory.putU4(Holly.ISP_FEED_CFG, isp_feed_cfg);
        Memory.putU4(Holly.SPAN_SORT_CFG, span_sort_cfg);

        Memory.putU4(Holly.SOFTRESET, softreset);
        Memory.putU4(Holly.SOFTRESET, 0);
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
}
