#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>
#include <stdbool.h>

typedef uint16_t pixel_t;

pixel_t pixel3_crear(bool r, bool g, bool b);
void pixel3_a_rgb(pixel_t pixel3, uint8_t *r, uint8_t *g, uint8_t *b);
pixel_t pixel12_crear(uint8_t r, uint8_t g, uint8_t b);
void pixel12_a_rgb(pixel_t pixel12, uint8_t *r, uint8_t *g, uint8_t *b);

pixel_t pixel4_crear(bool a, bool b, bool c, bool d);
void pixel4_a_abcd(pixel_t pixel4, uint8_t *a, uint8_t *b, uint8_t *c, uint8_t *d);


#endif //PIXEL_H
