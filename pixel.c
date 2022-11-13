#include "pixel.h"

pixel_t pixel3_crear(bool r, bool g, bool b){

    return (r << 2 ) | (g << 1) | (b);
}

void pixel3_a_rgb(pixel_t pixel3, uint8_t *r, uint8_t *g, uint8_t *b){

    *r = 255 * ((pixel3 >> 2) & 0x1);
    *g = 255 * ((pixel3 >> 1) & 0x1);
    *b = 255 * (pixel3 & 0x1);

}

pixel_t pixel12_crear(uint8_t r, uint8_t g, uint8_t b){
    return (r<<8)|(g<<4)|(b);
}

void pixel12_a_rgb(pixel_t pixel12, uint8_t *r, uint8_t *g, uint8_t *b){

    *r = ((pixel12 >> 8) & 0xf) << 4;
    *g = ((pixel12 >> 4) & 0xf) << 4;
    *b = (pixel12 & 0xf) << 4;

}
