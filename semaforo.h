#ifndef SEMAFORO_H
#define SEMAFORO_H

#define X_LARGADA   6
#define X_LLEGADA   4200

#include "imagen.h"
#include "figura.h"

typedef enum{
    APAGADO, AMARILLO, ROJO, VERDE, SIN_SEMAFORO, LLEGADA
}mef_semaforo_t;

typedef struct {
    enum figura figura;
    size_t paleta;
    int y;
    bool reflejar;
}semaforo_t;

mef_semaforo_t mef_semaforo(mef_semaforo_t estado, uint16_t *rom, imagen_t *cuadro, double tiempo, double x, double *ur, const pixel_t paleta[][16]);
void dibujar_semaforo(uint16_t *rom, double x, double xs,double tiempo, imagen_t *cuadro, const pixel_t paleta[][16], double *ur, const semaforo_t tabla_semaforo[]);

#endif
