#define STB_TRUETYPE_IMPLEMENTATION
#define ONEBIT_IMAGE_IMPLEMENTATION

// extern "C" {
#include "onebit.h"
#include "stb_truetype.h"
// }

void putPixel(int x, int y, int width, int height) { int byte = x / 8; }

int main(int argc, char *argv[]) {
  unsigned char ttf_buffer[100000];

  stbtt_fontinfo font;
  unsigned char *bitmap;
  int w, h, i, j, c = (argc > 1 ? atoi(argv[1]) : 'a'),
                  s = (argc > 2 ? atoi(argv[2]) : 20);

  fread(ttf_buffer, 1, 100000,
        fopen(argc > 3 ? argv[3] : "terminalf4.ttf", "rb"));

  stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0));
  bitmap = stbtt_GetCodepointBitmap(
      &font, 0, stbtt_ScaleForPixelHeight(&font, s), c, &w, &h, 0, 0);

  int stride = onebit_bmp_stride(w);
  unsigned char *img = (unsigned char *)malloc(stride * h);

  for (j = 0; j < h; ++j) {
    unsigned char *ptr = img + (h - j - 1) * stride;
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
  onebit_write_file_png1("aaasa.png", w, h, img);  
  onebit_write_file_bmp1("aaasa.bmp", w, h, img);
  free(img);
  free(bitmap);
  return 0;
}