#ifndef MOTO_H
#define MOTO_H

#include <stdbool.h>
#include <stdint.h>
#include "imagen.h"
#include "figura.h"

typedef struct moto moto_t;

/*Primitivas*/
moto_t *moto_crear();
void moto_destruir(moto_t *moto);
imagen_t *moto_get_figura(moto_t *moto, uint16_t *rom);


/*getters*/
double moto_get_velocidad(moto_t *moto);
double moto_get_x(moto_t *moto);
double moto_get_y(moto_t *moto);
int moto_get_intensidad(moto_t *moto);

bool moto_get_freno(moto_t *moto);
bool moto_get_acelerar(moto_t *moto);
bool moto_get_der(moto_t *moto);
bool moto_get_izq(moto_t *moto);
bool moto_get_colision(moto_t *moto);

/*setters*/
bool moto_set_velocidad(moto_t *moto, double vel);
bool moto_set_x(moto_t *moto, double x);
bool moto_set_y(moto_t *moto, double y);
bool moto_set_intensidad(moto_t *moto, int intensidad);

void moto_set_freno(moto_t *moto, bool freno);
void moto_set_acelerar(moto_t *moto, bool acelerar);
void moto_set_der(moto_t *moto, bool der);
void moto_set_izq(moto_t *moto, bool izq);
void moto_set_colision(moto_t *moto, bool colision);


#endif
