#include "moto.h"
#include <stdlib.h>
#include "fisica.h"
#include "math.h"

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
    PALETA_MOTO_0 = 0, PALETA_MOTO_1, PALETA_MOTO_2, PALETA_MOTO_3
};

/*
    TDA MOTO
    los valores de los distintos parametros son siempre validos
*/

struct moto {
    double velocidad;   //velocidad de la moto en km/h, de 0 a 279 km/h
    enum paleta_moto paleta;      //paleta a dibujar en un instante
    bool reflejar;      //se espeja la figura? // capaz me lo puedo ahorrar usando el giro y la intensidad
    double x;           //posicion en x respecto de la ruta (longitudinal)
    double y;           //posicion en y respecto de la ruta (perpendicular)
    bool freno;         //frenando?
    bool acelerar;      //acelerando?
    bool derecha;       //girando?
    bool izquierda;
    int intensidad;    //nivel de giro en ese instante de -3 a 3, negativo es izquierda
    bool colision;      // la moto colisiono con algo?
    double puntaje;
    bool morder;
    bool ganar;
    bool perder;
};


/*permite guardar las posiciones de cada imagen en las rom*/
struct moto_sprite {
    size_t pos;
    size_t ancho;
    size_t alto;
    size_t dibujado_x;
    size_t dibujado_y;
};

const struct moto_sprite tabla_sprites[4] = {
    [MOTO_1] =  {532, 36, 73, 144, 150},
    [MOTO_2] =  {5670, 36, 70, 126, 153},
    [MOTO_3] =  {11284, 46, 63, 126, 163},
    [MOTO_4] =  {17215, 60, 54, 126, 172}
};

moto_t *moto_crear(){
    moto_t *moto = malloc(sizeof(moto_t));
    if(moto == NULL) return NULL;

    moto->velocidad = 1;
    moto->paleta = PALETA_MOTO_0;
    moto->reflejar = false;
    moto->x = 0;
    moto->y = 0;
    moto->freno = false;
    moto->acelerar = false;
    moto->derecha = false;
    moto->izquierda = false;
    moto->intensidad = 0;
    moto->colision = 0;
    moto->morder = false;
    moto->ganar = false;
    moto->perder = false;
    return moto;
}

imagen_t *moto_get_figura(moto_t *moto, uint16_t *rom){

    int intensidad = abs(moto->intensidad);

    imagen_t *fig = obtener_figura(rom, tabla_sprites[intensidad].pos, tabla_sprites[intensidad].ancho, tabla_sprites[intensidad].alto);
    if(fig == NULL) return NULL;

    if(moto->intensidad < 0){
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

size_t moto_get_paleta(moto_t *moto){

    static double distancia_anterior = 0;

    if(moto->x - distancia_anterior > 2){
        distancia_anterior = moto->x;

        if(moto->freno){
            if(moto->paleta == PALETA_MOTO_2){
                return moto->paleta = PALETA_MOTO_3;
            }

            return moto->paleta = PALETA_MOTO_2;

        }

        if(moto->paleta == PALETA_MOTO_0){
            return moto->paleta = PALETA_MOTO_1;
        }

        return moto->paleta = PALETA_MOTO_0;
    }

    return moto->paleta;

}

double moto_dibujado_x(moto_t *moto){

    return tabla_sprites[abs(moto->intensidad)].dibujado_x;

}

double moto_dibujado_y(moto_t *moto){
    return tabla_sprites[abs(moto->intensidad)].dibujado_y;
}


void moto_computar_fisicas(moto_t *moto, double tiempo, double r, double tiempo_total){

    moto->x += posicion_x(moto->velocidad, tiempo);

    /*velocidad*/
    if((moto->acelerar) || (moto->velocidad < 80)){
        moto->velocidad = aceleracion(moto->velocidad, tiempo);
    }

    if(moto->freno){
        moto->velocidad = frenado(moto->velocidad, tiempo);
    }

    if(!moto->freno && !moto->acelerar){
        moto->velocidad = desaceleracion(moto->velocidad, tiempo);
    }

    moto->velocidad = morder_banquina(moto->velocidad, tiempo, moto->y);

    /*giros*/
    if(moto->derecha){
        moto->intensidad = intensidad_giro_derecha(moto->intensidad);
    }else if(moto->izquierda){
         moto->intensidad = intensidad_giro_izquierda(moto->intensidad);
    }else{
        moto->intensidad = reposo(moto->intensidad);
    }

    moto->y = posicion_y(moto->y, moto->intensidad);

    moto->y = irse_al_pasto(moto->y);

    moto->y = giro_de_ruta(moto->y, r, moto->velocidad, tiempo);

    moto->puntaje = puntaje(moto->velocidad, tiempo, moto->puntaje, moto->x);

    moto->ganar = ganar(moto->x);

    moto->perder = perder(tiempo_total);

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

double moto_get_puntaje(moto_t *moto){
    return moto->puntaje;
}

bool moto_get_ganar(moto_t *moto){
    return moto->ganar;
}

bool moto_get_perder(moto_t *moto){
    return moto->perder;
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

void moto_set_puntaje(moto_t *moto, double puntaje){
    moto->puntaje = puntaje;
}

