#ifndef MOTO_H
#define MOTO_H

#include <stdbool.h>
#include <stdint.h>
#include "imagen.h"
#include "figura.h"
#include "ruta.h"

typedef struct moto moto_t;

/*Primitivas*/
moto_t *moto_crear();
void moto_destruir(moto_t *moto);
imagen_t *moto_get_figura(moto_t *moto, uint16_t *rom);
double moto_dibujado_x(moto_t *moto);
double moto_dibujado_y(moto_t *moto);

void moto_computar_fisicas(moto_t *moto, double tiempo, double tiempo_total, const struct ruta *ruta, double *ur);

/*getters*/
double moto_get_velocidad(moto_t *moto);
double moto_get_x(moto_t *moto);
double moto_get_y(moto_t *moto);
int moto_get_intensidad(moto_t *moto);
size_t moto_get_paleta(moto_t *moto);

bool moto_get_freno(moto_t *moto);
bool moto_get_acelerar(moto_t *moto);
bool moto_get_der(moto_t *moto);
bool moto_get_izq(moto_t *moto);
bool moto_get_choque(moto_t *moto);
double moto_get_puntaje(moto_t *moto);
bool moto_get_ganar(moto_t *moto);
bool moto_get_perder(moto_t *moto);
bool moto_get_largada(moto_t *moto);

/*setters*/
bool moto_set_velocidad(moto_t *moto, double vel);
bool moto_set_x(moto_t *moto, double x);
bool moto_set_y(moto_t *moto, double y);
bool moto_set_intensidad(moto_t *moto, int intensidad);

void moto_set_freno(moto_t *moto, bool freno);
void moto_set_acelerar(moto_t *moto, bool acelerar);
void moto_set_der(moto_t *moto, bool der);
void moto_set_izq(moto_t *moto, bool izq);
void moto_set_choque(moto_t *moto, bool choque);
void moto_set_puntaje(moto_t *moto, double puntaje);
void moto_set_largada(moto_t *moto, bool largada);

#endif
