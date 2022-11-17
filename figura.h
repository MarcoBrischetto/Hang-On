#ifndef FIGURA_H
#define FIGURA_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "imagen.h"

#define CANTIDAD_VALORES_ROMS 229376
#define BYTES_POR_ROM         32768

#define ROM_6819    "roms/6819.rom"
#define ROM_6820    "roms/6820.rom"

#define ROM_6821    "roms/6821.rom"
#define ROM_6822    "roms/6822.rom"

#define ROM_6823    "roms/6823.rom"
#define ROM_6824    "roms/6824.rom"

#define ROM_6825    "roms/6825.rom"
#define ROM_6826    "roms/6826.rom"

#define ROM_6827    "roms/6827.rom"
#define ROM_6828    "roms/6828.rom"

#define ROM_6829    "roms/6829.rom"
#define ROM_6830    "roms/6830.rom"

#define ROM_6845    "roms/6845.rom"
#define ROM_6846    "roms/6846.rom"

bool cargar_figuras_rom(uint16_t rom[CANTIDAD_VALORES_ROMS]);
imagen_t *obtener_figura(uint16_t rom[CANTIDAD_VALORES_ROMS], size_t pos, size_t ancho, size_t alto);

#endif
