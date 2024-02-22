#ifndef FISICA_H
#define FISICA_H

#include <stdbool.h>
#include <stddef.h>

#define TIEMPO_CHOQUE 5

double posicion_x(double velocidad, double t);
double aceleracion(double velocidad, double t);
double frenado(double velocidad, double t);
double desaceleracion(double velocidad, double t);
double morder_banquina(double velocidad, double t, double posicion);
int intensidad_giro_derecha(int intensidad);
int intensidad_giro_izquierda(int intensidad);
int reposo(int intensidad);
double posicion_y(double posicion, int intensidad);
double irse_al_pasto(double posicion);
double giro_de_ruta(double posicion, double r, double velocidad, double t);
double puntaje(double velocidad, double tiempo, double puntaje, double posicion, double y);
bool ganar(double posicion);
bool perder(double t_total);
bool choque(double yx, double ym, double ancho);

#endif
