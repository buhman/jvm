import struct
import sys

from PIL import Image

class color_format:
    def gbgr1555(r, g, b, a): # nintendo ds
        r5 = (r >> 3) & 31
        g6 = (g >> 3) & 31
        g6_l = (g >> 2) & 1
        b5 = (b >> 3) & 31
        return (g6_l << 15) | (b5 << 10) | (g6 << 5) | (r5 << 0)

    def argb4444(r, g, b, a):
        a4 = (a >> 4) & 15
        r4 = (r >> 4) & 15
        g4 = (g >> 4) & 15
        b4 = (b >> 4) & 15
        return (a4 << 12) | (r4 << 8) | (g4 << 4) | (b4 << 0)

    def argb1555(r, g, b, a):
        a1 = (a >> 7) & 1
        r5 = (r >> 3) & 31
        g5 = (g >> 3) & 31
        b5 = (b >> 3) & 31
        return (a1 << 15) | (r5 << 10) | (g5 << 5) | (b5 << 0)

    def rgb565(r, g, b, a):
        r5 = (r >> 3) & 31
        g6 = (g >> 2) & 63
        b5 = (b >> 3) & 31
        return (r5 << 11) | (g5 << 5) | (b5 << 0)

    def axxx4444(r, g, b, a):
        a4 = (a >> 4) & 15
        return (a4 << 12)

    def from_string(s):
        return dict([
            ("gbgr1555", color_format.gbgr1555),
            ("argb4444", color_format.argb4444),
            ("argb1555", color_format.argb1555),
            ("rgb565", color_format.rgb565),
            ("axxx4444", color_format.axxx4444),
        ])[s]

def convert_colors(f, convert, colors):
    assert len(colors) % 2 == 0, len(colors)
    #f.write(struct.pack("<I", (len(colors) * 2) // 4))
    for color in colors:
        value = convert(*color)
        f.write(struct.pack("<H", value))

def convert_indices(f, palette, pixels):
    if len(palette) <= 4:
        for i in range(len(pixels) // 4):
            a = pixels[i * 4 + 0]
            b = pixels[i * 4 + 1]
            c = pixels[i * 4 + 2]
            d = pixels[i * 4 + 3]
            assert a <= 3 and b <= 3 and c <= 3 and d <= 3, (a, b, c, d)
            pixel = (d << 6) | (c << 4) | (b << 2) | (a << 0)
            f.write(struct.pack("<B", pixel))
    elif len(palette) <= 16:
        for i in range(len(pixels) // 2):
            a = pixels[i * 2 + 0]
            b = pixels[i * 2 + 1]
            assert a <= 15 and b <= 15, (a, b)
            pixel = (b << 4) | (a << 0)
            f.write(struct.pack("<B", pixel))
    elif len(palette) <= 256:
        for pixel in pixels:
            assert pixel <= 255
            f.write(struct.pack("<B", pixel))
    else:
        assert False, len(palette)

if __name__ == "__main__":
    in_file = sys.argv[1]
    format = sys.argv[2]
    out_file = sys.argv[3]

    convert = color_format.from_string(format)

    with Image.open(in_file) as im:
        if not im.palette:
            pixels = list(im.convert("RGBA").getdata())
            with open(out_file, 'wb') as f:
                convert_colors(f, convert, pixels)
        else:
            pixels = list(im.convert("P").getdata())
            palette = list(im.palette.colors)
            with open(out_file, 'wb') as f:
                convert_indices(f, palette, pixels)
            with open(out_file + '.pal', 'wb') as f:
                convert_colors(f, convert, [(*c, 255) for c in palette])
