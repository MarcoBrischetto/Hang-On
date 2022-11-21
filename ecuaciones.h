#ifndef ECUACIONES_H
#define ECUACIONES_H

#include "ruta.h"

#define POSICIONES_VECTOR 96

double v(double d);
double d(double v);
double escalado_h(double v, unsigned int h0);
double escalado_ancho(double v, unsigned int a0);
void desplazamiento_lateral(double *ul, double ym);
void desplazamiento_curva(double *uc, const struct ruta *r, double xm);
void desplazamiento_total(double *uc, double *ul, double *ur);
double u(double yx, double v, double u0);


#endif
