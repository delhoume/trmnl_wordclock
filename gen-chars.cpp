#include <cstdint>
#define STB_TRUETYPE_IMPLEMENTATION
#define ONEBIT_IMAGE_IMPLEMENTATION

// extern "C" {
#include "onebit.h"
#include "stb_truetype.h"
// }

void putPixel(int x, int y, int width, int height) { int byte = x / 8; }

int main(int argc, char *argv[]) {
  uint8_t  ttf_buffer[100000];

  stbtt_fontinfo font;
  int w, h, i, j;
  const char *str = "THEQUICKBROWNFOXJUMPSOVERTHELAZYDOG";
  int size = 200;

  fread(ttf_buffer, 1, 100000,
        fopen(argc > 3 ? argv[3] : "terminalf4.ttf", "rb"));

  stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0));

  float scale = stbtt_ScaleForPixelHeight(&font, size);

  int ascent,descent, linegap, baseline,ch=0;
    int x0, y0, x1, y1  = 0;
   stbtt_GetFontBoundingBox(&font, &x0, &y0, &x1, &y1);
   stbtt_GetFontVMetrics(&font, &ascent,&descent,&linegap);
   baseline = (int) (ascent* scale);
   int full_char_width = (x1 - x0) * scale;
   int full_char_height = (y1 - y0) * scale;
   int full_char_stride = onebit_bmp_stride(full_char_width);
   uint8_t* char_data = (uint8_t*)malloc(full_char_stride * full_char_height);
   fprintf(stdout, "font %d %d\n", full_char_width, full_char_height);

  for(int idx = 0; idx < strlen(str); idx++) {
    int offsetx = 0, offsety = 0;
    int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&font, str[idx], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);
        int w = c_x2 - c_x1;
        int h = c_y2 - c_y1;
    /* compute y (different characters have different heights) */
    uint8_t* bitmap = (uint8_t*)malloc(w * h);
    stbtt_MakeCodepointBitmap(&font, bitmap, w, h, w, scale, scale, str[idx]);
   memset(char_data, 255, full_char_stride * full_char_height);
   int xoffset = (full_char_width - w) / 2;
    int yoffset = (full_char_height - h) / 2;
   fprintf(stdout, "char %c %d %d\n", str[idx], w, h);
    for (j = 0; j < h; ++j) {
      unsigned char *ptr = char_data + (h - j + yoffset - 1) * full_char_stride + xoffset / 8;
      for (i = 0; i < w; ++i) {
        int pos = i / 8;
        uint8_t mask = 1 << (7 - (i % 8));
        if (bitmap[j * w + i] > 0) {
          ptr[pos] &= ~mask;
        } else {
          ptr[pos] |= mask;
        }
      }
    }
    char buf[32];
    snprintf(buf,32, "letters/%c_full.png", str[idx]);
    onebit_write_file_png1(buf, full_char_width, full_char_height, char_data);
    free(bitmap);
  }
  free(char_data);
  return 0;
}