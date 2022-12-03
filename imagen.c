#include "imagen.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct imagen{
	pixel_t **pixeles;
	size_t ancho, alto;
};

imagen_t *_imagen_crear(size_t ancho, size_t alto){

	imagen_t *pImg = malloc(sizeof(imagen_t));

	if(pImg == NULL)
		return NULL;

	pImg->pixeles = malloc(alto*sizeof(pixel_t*));

	if(pImg->pixeles == NULL){
		free(pImg);
		return NULL;
	}

	for(size_t i = 0; i < alto; i++){

		pImg->pixeles[i] = malloc(ancho*sizeof(pixel_t));

		if(pImg->pixeles[i] == NULL){
			pImg->alto = i + 1;
			imagen_destruir(pImg);
			return NULL;
		}
	}

	pImg->ancho = ancho;
	pImg->alto = alto;

	return pImg;
}


void imagen_destruir(imagen_t *imagen){

	for(size_t i = 0; i < imagen->alto; i++){
		free(imagen->pixeles[i]);
	}

	free(imagen->pixeles);
	free(imagen);
}

imagen_t *imagen_generar(size_t ancho, size_t alto, pixel_t valor){

	imagen_t *pImg = _imagen_crear(ancho, alto);

	if(pImg == NULL)
		return NULL;

	for(size_t f = 0; f < alto; f++){
		for(size_t c = 0; c < ancho; c++){
			pImg->pixeles[f][c] = valor;
		}
	}

	return pImg;
}

imagen_t *imagen_leer_pgm(){

	char aux[MAX_STR];
	size_t ancho, alto;
	char *pEnd;

	fgets(aux, MAX_STR, stdin);

	if(strcmp(aux, "P2\n"))
		return NULL;

	fgets(aux, MAX_STR, stdin);

	ancho = strtol(aux, &pEnd, 10);
	alto = strtol(pEnd, &pEnd, 10);

	imagen_t *pImg = _imagen_crear(ancho, alto);

	if(pImg == NULL)
		return NULL;

	fgets(aux, MAX_STR, stdin); //ignora el maximo

	for(size_t f = 0; f < alto; f++){
		for(size_t c = 0; c < ancho; c++){
			if(fgets(aux, MAX_STR, stdin) == NULL){
				imagen_destruir(pImg);
				return NULL;
			}
			pImg->pixeles[f][c] = strtol(aux, &pEnd, 10);
		}
	}

	return pImg;
}

void imagen_imprimir_pgm(const imagen_t *imagen){

	printf("P2\n%zd %zd\n255\n",imagen->ancho, imagen->alto);

	for(size_t f = 0; f < imagen->alto; f++){
		for(size_t c = 0; c < imagen->ancho; c++){
			printf("%d\n", imagen->pixeles[f][c]);
		}
	}
}

void imagen_pegar(imagen_t *destino, imagen_t *origen, int x, int y, bool reflejar){

	imagen_t *o = origen;

	if(reflejar) o = imagen_reflejar(origen);

	for(int f = y >= 0 ? 0 : -y; f < o->alto && f + y < destino->alto; f++)
		for(int c = x >= 0 ? 0 : -x; c < o->ancho && c + x < destino->ancho; c++){
			if(o->pixeles[f][c] != 0)
				destino->pixeles[f+y][c+x] = o->pixeles[f][c];
	}

	if(reflejar) imagen_destruir(o);

}

imagen_t *imagen_escalar(const imagen_t *origen, size_t ancho_destino, size_t alto_destino){

	double escala_x = (double)origen->ancho/ancho_destino;
	double escala_y = (double)origen->alto/alto_destino;

	imagen_t *pDestino = _imagen_crear(ancho_destino, alto_destino);

	if(pDestino == NULL)
		return NULL;

	for(size_t f = 0; f < alto_destino; f++){
		for(size_t c = 0; c < ancho_destino; c++){
			pDestino->pixeles[f][c] = origen->pixeles[(size_t)(f*escala_y)][(size_t)(c*escala_x)];
		}
	}

	return pDestino;
}

size_t imagen_get_ancho(const imagen_t *im){

	return im->ancho;
}

size_t imagen_get_alto(const imagen_t *im){

    return im->alto;
}


pixel_t imagen_get_pixel(const imagen_t *im, size_t x, size_t y){

    return im->pixeles[y][x];
}

bool imagen_set_pixel(const imagen_t *im, size_t x, size_t y, pixel_t p){


	if(x > im->ancho || x < 0) return false;
	if(y > im->alto || y < 0 ) return false;


	im->pixeles[y][x] = p;

    return true;
}

/*
	funcion: reflejar imagen
	recibe una imagen y devuelve una imagen nueva con su reflejo
*/

imagen_t *imagen_reflejar(const imagen_t *im){

	imagen_t *reflejada = imagen_generar(im->ancho, im->alto, 0);
	if(reflejada == NULL) return NULL;

	for(size_t f = 0; f < reflejada->alto; f++){
		for(size_t c = 0; c < reflejada->ancho; c++){
			reflejada->pixeles[f][c] = im->pixeles[f][im->ancho - c - 1]; //-1 para no pisar fuera de memoria
		}
	}

	return reflejada;

}

void imagen_pegar_con_paleta(imagen_t *destino, imagen_t *origen, int x, int y, const pixel_t paleta[], bool reflejar){

	imagen_t *o = origen;

	if(reflejar) o = imagen_reflejar(origen);

	for(int f = y >= 0 ? 0 : -y; f < o->alto && f + y < destino->alto; f++)
		for(int c = x >= 0 ? 0 : -x; c < o->ancho && c + x < destino->ancho; c++){
			if(o->pixeles[f][c] != 0)
				destino->pixeles[f+y][c+x] = paleta[o->pixeles[f][c]];
	}

	if(reflejar) imagen_destruir(o);

}


void imagen_escribir_ppm(const imagen_t *im, FILE *fo, void (*pixel_a_rgb)(pixel_t, uint8_t *, uint8_t *, uint8_t *)){

	uint8_t r, g, b;

	fputs("P3\n",fo);
	fprintf(fo, "%zd %zd\n255\n", im->ancho, im->alto);

	for(size_t f = 0; f < im->alto; f++){
		for(size_t c = 0; c < im->ancho; c++){
			pixel_a_rgb(im->pixeles[f][c], &r, &g, &b);
			fprintf(fo, "%d %d %d\n", r, g, b);
		}
	}

}

bool imagen_guardar_ppm(const imagen_t *im, const char *fn, void (*pixel_a_rgb)(pixel_t, uint8_t *, uint8_t *, uint8_t *)){

	FILE *file = fopen(fn,"w");
	if(file == NULL) return false;

	imagen_escribir_ppm(im, file, pixel_a_rgb);

	if(fclose(file)) return false;

	return true;
}

/*
	funcion: imagen_a_textura
	recibe una imagen im y la vuelca en un vector v segun la convencion de SDL2
*/

void imagen_a_textura(const imagen_t *im, uint16_t *v){

	for(size_t f = 0; f < im->alto; f++){
		memcpy(v + (f * im->ancho), im->pixeles[f], im->ancho * sizeof(pixel_t));
	}

}


/*
	funcion: imagen_pegar_fila_con_paleta
	pega una fila determinada de una imagen con una paleta
*/

void imagen_pegar_fila_con_paleta(imagen_t *destino, const imagen_t *origen, int x, int y, const pixel_t paleta[], size_t f){

	for(int c = x >= 0 ? 0 : -x; c < origen->ancho && c + x < destino->ancho; c++){
		if(origen->pixeles[f][c] != 0)
			destino->pixeles[y][c+x] = paleta[origen->pixeles[f][c]];
	}
}

