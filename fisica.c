#include "fisica.h"
#include <math.h>
#include <stdlib.h>

/*
    Indica los niveles de giro posibles
*/

const int tabla_intensidades[] = {
    0,
    3,
    9,
    15
};

double posicion_x(double velocidad, double t){
    if(velocidad < 0) return 0;
    return t*(velocidad/3.6)*1.0;
}

double aceleracion(double velocidad, double t){

     return (279 - (279 - velocidad) * exp(-0.224358*t));
}

double frenado(double velocidad, double t){
    if(velocidad > 80)
        return 1.0*velocidad - (300*t);
    return velocidad;
}

double desaceleracion(double velocidad, double t){
    if(velocidad > 80)
        return velocidad - 90*t;
    return velocidad;

}

double morder_banquina(double velocidad, double t, double posicion){
    if(velocidad > 92 && abs(posicion) > 215)
        return velocidad - 3;

    return velocidad;
}

int intensidad_giro_derecha(int intensidad){

    intensidad++;
    if(intensidad > 3) intensidad = 3;

    return intensidad;
}

int intensidad_giro_izquierda(int intensidad){

    intensidad--;
    if(intensidad < -3) intensidad = -3;

    return intensidad;
}

int reposo(int intensidad){

    if(intensidad < 0) intensidad++;
    if(intensidad > 0) intensidad--;

    return intensidad;
}

double posicion_y(double posicion, int intensidad){

    if(intensidad >= 0)
        return posicion + tabla_intensidades[intensidad];
    else
        return posicion - tabla_intensidades[-intensidad];
}

double irse_al_pasto(double posicion){
    if(posicion > 435) return 435;
    if(posicion < -435) return -435;

    return posicion;
}

double giro_de_ruta(double posicion, double r, double velocidad, double t){
    return posicion - 2.5*posicion_x(velocidad,t)*r;
}

double puntaje(double velocidad, double tiempo, double puntaje, double posicion, double y){
    if(abs(y) > 215) return puntaje;
    if(velocidad < 117) return  puntaje + 125*posicion_x(velocidad, tiempo);

    return  puntaje + posicion_x(velocidad, tiempo)*(3.13*velocidad - 240);

}

bool ganar(double posicion){
    if(posicion >= 4200) return true;
    return false;
}

bool perder(double t_total){
    if(t_total <= 0) return true;
    return false;
}

bool choque(double yx, double ym, double ancho){

    if(ym > yx-(ancho/2.0) && ym < yx+(ancho/2.0))
        return true;

    return false;
}

