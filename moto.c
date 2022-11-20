#include "moto.h"
#include <stdlib.h>

/*
    TODO:  -la moto misma va a devolver que hay que dibujar
            se pueden hacer getters para saber en que posicion y demas
        -ver prioridades de giro
        -ver tema de la intensidad de giro, hace falta que tenga getter y setter?
        -fuerzo el maximo si ingresan valores no validos?
        -ver si no conviene expresar el movimiento de otra manera
        -capaz no vale la pena poner la figura y el reflejo y solamente usar intensidad de giro
        -ver posicionamiento a la hora de girar
 */

enum figura_moto {
    MOTO_1 = 0, MOTO_2, MOTO_3, MOTO_4
};

enum paleta_moto{
    PALETA_MOTO_0, PALETA_MOTO_1, PALETA_MOTO_2, PALETA_MOTO_3
};

/*
    TDA MOTO
    los valores de los distintos parametros son siempre validos
*/

struct moto {
    double velocidad;   //velocidad de la moto en m/s, de 0 a 279 km/h o 77.5 m/s
    enum figura_moto figura;      //indice de la figura a dibujar en ese instante
    enum paleta_moto paleta;      //paleta a dibujar en un instante
    bool reflejar;      //se espeja la figura? // capaz me lo puedo ahorrar usando el giro y la intensidad
    double x;           //posicion en x respecto de la ruta (longitudinal)
    double y;           //posicion en y respecto de la ruta (perpendicular)
    bool freno;         //frenando?
    bool acelerar;      //acelerando?
    bool derecha;       //girando?
    bool izquierda;
    int intensidad;    //nivel de giro en ese instante de 0 - 3, 0 minimo
    bool colision;      // la moto colisiono con algo?
};


/*permite guardar las posiciones de cada imagen en las rom*/
struct moto_sprite {
    size_t pos;
    size_t ancho;
    size_t alto;
};

const struct moto_sprite tabla_sprites[4] = {
    [MOTO_1] =  {532, 36, 73},
    [MOTO_2] =  {5670, 36, 70},
    [MOTO_3] =  {11284, 46, 63},
    [MOTO_4] =  {17215, 60, 54}
};

moto_t *moto_crear(){
    moto_t *moto = malloc(sizeof(moto_t));
    if(moto == NULL) return NULL;

    moto->velocidad = 0;
    moto->figura = MOTO_1;
    moto->paleta = PALETA_MOTO_0;
    moto->reflejar = false;
    moto->x = 0;
    moto->y = 162;
    moto->freno = false;
    moto->acelerar = false;
    moto->derecha = false;
    moto->izquierda = false;
    moto->intensidad = 0;
    moto->colision = 0;

    return moto;
}

imagen_t *moto_get_figura(moto_t *moto, uint16_t *rom){

    imagen_t *fig = obtener_figura(rom, tabla_sprites[moto->intensidad].pos, tabla_sprites[moto->intensidad].ancho, tabla_sprites[moto->intensidad].alto);
    if(fig == NULL) return NULL;

    if(moto->izquierda){
        imagen_t *aux  = imagen_reflejar(fig);

        if(aux == NULL){
            imagen_destruir(fig);
            return NULL;
        }

        imagen_destruir(fig);
        fig = aux;

    }

    return fig;
}


void moto_destruir(moto_t *moto){
    free(moto);
}

/*getters*/
double moto_get_velocidad(moto_t *moto){
    return moto->velocidad;
}

double moto_get_x(moto_t *moto){
    return moto->x;
}

double moto_get_y(moto_t *moto){
    return moto->y;
}

int moto_get_intensidad(moto_t *moto){
    return moto->intensidad;
}

bool moto_get_freno(moto_t *moto){
    return moto->freno;
}

bool moto_get_acelerar(moto_t *moto){
    return moto->acelerar;
}

bool moto_get_der(moto_t *moto){
    return moto->derecha;
}

bool moto_get_izq(moto_t *moto){
    return moto->izquierda;
}

bool moto_get_colision(moto_t *moto){
    return moto->colision;
}

/*setters*/

bool moto_set_velocidad(moto_t *moto, double vel){
    /*conversion?*/
    moto->velocidad = vel;
    return true;
}

bool moto_set_x(moto_t *moto, double x){
    /*limites?*/
    moto->x = x;
    return true;
}

bool moto_set_y(moto_t *moto, double y){
    moto->y = y;
    return true;
}

bool moto_set_intensidad(moto_t *moto, int intensidad){
    moto->intensidad = intensidad;
    return true;
}

void moto_set_freno(moto_t *moto, bool freno){
    moto->freno = freno;
}

void moto_set_acelerar(moto_t *moto, bool acelerar){
    moto->acelerar = acelerar;
}

void moto_set_der(moto_t *moto, bool der){
    moto->derecha = der;
}

void moto_set_izq(moto_t *moto, bool izq){
    moto->izquierda = izq;
}

void moto_set_colision(moto_t *moto, bool colision){
    /*TODO modificar segun sea necesario*/
    moto->colision = colision;
}
