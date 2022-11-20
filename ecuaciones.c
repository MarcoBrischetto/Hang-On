#include "ecuaciones.h"
#include <math.h>

/*
    funcion: v
    calcula la distancia a la que se debera dibujar un objeto
    en la pantalla v en funcion de una distancia d
*/

double v(double d){
    //TODO podira chquear d por las dudas
    return (96-96*exp(-0.11*d));
}

/*
    funcion: d
    hace el calculo inverso de la funcion v
*/

double d(double v){

    return -(1/0.11)*log(1-(v/96));
}


/*
    funcion: escalado_h
    calcula la altura del objeto escalado segun su altura
    en v = 0 h0 y la distancia a la que se encuentra v
*/

double escalado_h(double v, unsigned int h0){

    return h0*(1-(v/96)) + (5*v/96);
}

/*
    funcion: escalado_ancho
    calcula el ancho del objeto escalado segun su ancho
    en v = 0 a0 y la distancia a la que se encuentra v
*/

double escalado_ancho(double v, unsigned int a0){
    double res =  a0*(1-(v/96)) + (5*v/96);

    return (res < 3)? 3 : res;
}

/*
    funcion: desplazamiento_lateral
    Calcula el desplazamiento lateral de la ruta en funcion de la
    posicion de la moto ym y la posicion de la linea de la ruta v
*/

void desplazamiento_lateral(double *ul, double ym){

    for(size_t v = 0; v < POSICIONES_VECTOR; v++)
        ul[v] = -ym*(1-(v/96));

}

/*
    funcion:


 */

/*
    funcion: desplazamiento_curva
    recibe un vector de al menos POSICIONES_VECTOR y guarda en el
    los desplazamientos de curvatura. Para ello recibe una struct r
    con informacion de la ruta.
*/
void desplazamiento_curva(double *uc, const struct ruta *r){

    uc[0] = 0;

    for(size_t v = 1; v < POSICIONES_VECTOR; v++)
        uc[v] = uc[v-1] + r[(int)d(v)].radio_curva*exp(0.105*v-8.6);

}

/*
    funcion: u
    Calcula la posicion u de un objeto en funcion del desplazamiento u0
    , su posicion v y su TODO
*/
/*
void u(double yx, double *v, double u0){

    return  yx*(1-(v/96)) + ((u0*v)/5000) + ur
}
*/
