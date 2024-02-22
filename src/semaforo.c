#include "semaforo.h"
#include "ecuaciones.h"

/*
    Tablas para las distintas formas del
    semaforo
*/

const semaforo_t tabla_semaforo_apagado[] = {

    {SEMAFORO, 41, 210, 1},
    {SEMAFORO, 41, -210, 0},
    {VIGA, 45, 145, 0},
    {VIGA, 45, -145, 0},
    {BANNER, 45, 0, 0}

};

const semaforo_t tabla_semaforo_amarillo[] = {

    {SEMAFORO, 42, 210, 1},
    {SEMAFORO, 42, -210, 0},
    {VIGA, 45, 145, 0},
    {VIGA, 45, -145, 0},
    {BANNER, 45, 0, 0}

};

const semaforo_t tabla_semaforo_rojo[] = {

    {SEMAFORO, 43, 210, 1},
    {SEMAFORO, 43, -210, 0},
    {VIGA, 45, 145, 0},
    {VIGA, 45, -145, 0},
    {BANNER, 45, 0, 0},
};

const semaforo_t tabla_semaforo_verde[] = {
    {SEMAFORO, 44, 210, 1},
    {SEMAFORO, 44, -210, 0},
    {VIGA, 45, 145, 0},
    {VIGA, 45, -145, 0},
    {BANNER, 45, 0, 0}
};

const semaforo_t tabla_semaforo_llegada[] = {
    {SEMAFORO, 41, 210, 1},
    {SEMAFORO, 41, -210, 0},
    {VIGA, 45, 145, 0},
    {VIGA, 45, -145, 0},
    {BANNER, 47, 0, 0}
};

/*
    funcion: mef_semaforo
    Maquina de estados finita que se encarga del dibujado del semaforo
    segun el tiempo, la posicion de la moto xm, el radio de curva ur
*/

mef_semaforo_t mef_semaforo(mef_semaforo_t estado, uint16_t *rom, imagen_t *cuadro, double tiempo, double xm, double *ur, const pixel_t paleta[][16]){

    switch(estado){

        case APAGADO:

            dibujar_semaforo(rom, xm, X_LARGADA, tiempo, cuadro, paleta, ur, tabla_semaforo_apagado);

            if(tiempo > 1) estado = AMARILLO;

            break;

        case AMARILLO:

            dibujar_semaforo(rom, xm, X_LARGADA, tiempo, cuadro, paleta, ur, tabla_semaforo_amarillo);

            if(tiempo > 2) estado = ROJO;

            break;

        case ROJO:

            dibujar_semaforo(rom, xm, X_LARGADA, tiempo, cuadro, paleta, ur, tabla_semaforo_rojo);

            if(tiempo > 3) estado = VERDE;

            break;

        case VERDE:

            dibujar_semaforo(rom, xm, X_LARGADA, tiempo, cuadro, paleta, ur, tabla_semaforo_verde);

            if(xm >= 6) estado = SIN_SEMAFORO;

            break;

        case SIN_SEMAFORO:

            if(xm > X_LLEGADA - CAMPO_VISION) estado = LLEGADA;

            break;

        case LLEGADA:

            dibujar_semaforo(rom, xm, X_LLEGADA, tiempo, cuadro, paleta, ur, tabla_semaforo_llegada);

            break;

        default:

            break;
    }

    return estado;
}

/*
    Funcion: dibujar_semaforo
    Se encarga del calculo de como escalar y posicionar el semaforo segun la posicion de la moto xm y su posicion xs
    y de pegarla en el cuadro
*/

void dibujar_semaforo(uint16_t *rom, double xm, double xs,double tiempo, imagen_t *cuadro, const pixel_t paleta[][16], double *ur, const semaforo_t tabla_semaforo[]){

        int d = xs - xm;

        imagen_t *imagen;

        for(size_t i = 0; i < 5; i++){

            enum figura figura = tabla_semaforo[i].figura;

            size_t alto = tabla_figuras[figura].alto;

            imagen_t *imagen_rom = obtener_figura(rom, tabla_figuras[figura].pos, tabla_figuras[figura].ancho, alto);

            if(figura == VIGA || figura == BANNER){
                alto = 249;
                imagen = imagen_generar(tabla_figuras[figura].ancho, alto, 0);
                imagen_pegar(imagen, imagen_rom, 0, 0, false);
                imagen_destruir(imagen_rom);
            }
            else imagen = imagen_rom;


            double alto_escalado = escalado_h(v(d), alto);
            double ancho_escalado = escalado_ancho(v(d), tabla_figuras[figura].ancho);

            imagen_t *img_fig_escalada = imagen_escalar(imagen, ancho_escalado, alto_escalado);

            imagen_destruir(imagen);

            size_t idx_paleta = tabla_semaforo[i].paleta;
            int yx = tabla_semaforo[i].y;
            bool reflejar = tabla_semaforo[i].reflejar;

            double pos_u = u(yx, v(d), ur) + U - ancho_escalado/2;
            double pos_v = V - v(d) - alto_escalado;

            imagen_pegar_con_paleta(cuadro, img_fig_escalada, pos_u, pos_v, paleta[idx_paleta], reflejar);

            imagen_destruir(img_fig_escalada);
        }

}

