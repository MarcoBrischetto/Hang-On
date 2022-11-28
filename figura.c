#include "figura.h"
#include <stdio.h>

/*
const char tabla_roms[][]{



};
*/

const struct figura_sprite tabla_figuras[] = {
    [ARBOL] =   {50116, 46, 188},
    [CARTEL] =  {37390, 96, 112},
    [ROCA] =    {69464, 136, 76},
    [BELL] =    {82922, 63, 146},
    [FORUM] =   {89102, 118, 114},
    [DELFIN] =  {119280, 144, 110},
    [SEMAFORO] = {0,0,0},
    [BANNER] = {0,0,0},
    [VIGA] = {0,0,0},
    [GOAL]  =   {194556, 140, 47}, //141 48
    [NO_FIG] = {0,0,0}

};

/*
    funcion: cargar_par_rom

    compone dos roms(ms y ls) y las carga en el vector rom en la posicion pos de inicio
    se asume que todos los pares de roms ocupan lo mismo
*/

static bool cargar_par_rom(char *r_ms_rom, char *r_ls_rom, uint16_t rom[CANTIDAD_VALORES_ROMS], size_t pos){

    FILE *ms_rom = fopen(r_ms_rom, "rb");

    if(rom == NULL) return false;

    FILE *ls_rom = fopen(r_ls_rom, "rb");

    if(rom == NULL){
        fclose(ms_rom);
        return false;
    }

    uint16_t bloque;
    uint16_t msb = 0, lsb = 0;

    for(size_t i = 0; i < BYTES_POR_ROM; i++){

        fread(&msb, 1, 1, ms_rom);
        fread(&lsb, 1, 1, ls_rom);

        bloque = (msb << 8) + lsb;

        rom[i + pos] = bloque;
    }


    //if(fclose(ms_rom) || fclose(ls_rom)) return false;

    fclose(ms_rom);
    fclose(ls_rom);

    return true;

}


/*
    funcion: cargar_par_rom

    carga todas las roms en el en el vector rom
*/

bool cargar_figuras_rom(uint16_t rom[CANTIDAD_VALORES_ROMS]){

    if(!cargar_par_rom( ROM_6820, ROM_6819, rom, 0)) return false;
    if(!cargar_par_rom( ROM_6822, ROM_6821, rom, BYTES_POR_ROM)) return false;
    if(!cargar_par_rom( ROM_6824, ROM_6823, rom, BYTES_POR_ROM * 2 )) return false;
    if(!cargar_par_rom( ROM_6826, ROM_6825, rom, BYTES_POR_ROM * 3 )) return false;
    if(!cargar_par_rom( ROM_6828, ROM_6827, rom, BYTES_POR_ROM * 4 )) return false;
    if(!cargar_par_rom( ROM_6830, ROM_6829, rom, BYTES_POR_ROM * 5 )) return false;
    if(!cargar_par_rom( ROM_6846, ROM_6845, rom, BYTES_POR_ROM * 6 )) return false;

    return true;
}

/*
    funcion: obtener_figura

    devuelve una imagen ancho x alto de la figura pedida en la posocion pos del vector rom
*/

imagen_t *obtener_figura(uint16_t rom[CANTIDAD_VALORES_ROMS], size_t pos, size_t ancho, size_t alto){

    imagen_t *fig = imagen_generar(ancho, alto, 0);
    if(fig == NULL) return NULL;

    bool nueva_linea = 1;

    size_t f = 0, c = 0;

    for(size_t i = pos; i < pos + (ancho*alto-ancho)/4; i++){

        if(c >= ancho) c = 0;

        //mientras sea nueva linea y sea 0xf, saltea

        if(nueva_linea && ((rom[i] & 0xf) == 0xf))
            continue;

        nueva_linea = 0;

        //si es 0xf, lo cambio a 0

        for(size_t j = 0; j < 4; j++){
            uint16_t aux;
            pixel_t pixel = ((aux = ((rom[i] >> (12 - j * 4)) & 0xf)) == 0xf)? 0 : aux;
            //uint8_t pixel = (rom[i] >> (12 - j * 4)) & 0xf;
            imagen_set_pixel(fig, c + j, f, pixel);
        }

        if((rom[i] & 0xf) == 0xf){
            c = 0;
            f++;
            nueva_linea = 1;
            continue;
        }

        c+=4;   //salto de a 4 porque leo de a 4 pixeles
    }

    return fig;

}

