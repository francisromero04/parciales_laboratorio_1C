#ifndef Peliculas_H_
#define Peliculas_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

#define TAM_CODIGO 7
#define TAM_CADENA 20

typedef struct
{
	int id;
	char titulo[30];
	float rating;
	char genero[30];
}Peliculas;

Peliculas* Peliculas_new();
Peliculas* new_PeliculasConParametros(char* idStr, char* tituloStr, char* generoStr, char* rating);

void Peliculas_delete();

int Pelicula_SetId(Peliculas* pelicula, int id);
int Pelicula_GetId(Peliculas* pelicula, int* id);

int Pelicula_SetTitulo(Peliculas* pelicula, char* titulo);
int Pelicula_GetTitulo(Peliculas* pelicula, char* titulo);

int Pelicula_SetGenero(Peliculas* pelicula, char* genero);
int Pelicula_GetGenero(Peliculas* pelicula, char* genero);

int Pelicula_GetGeneroDescripcion(int numero, char* Genero);

int Pelicula_SetRating(Peliculas* pelicula, float rating);
int Pelicula_GetRating(Peliculas* pelicula, float* rating);

void Peliculas_imprimir(Peliculas* pelicula);

int Pelicula_OrdenamientoPorGeneroRating(void* punteroUno, void* punteroDos);

int Pelicula_FiltrarDrama(void* elemento);

void* Peliculas_mapGenero(void* pElement);

void* Peliculas_mapRating(void* a);

int Peliculas_actualizarUltimoId(int idViejo);

#endif /* Peliculas_H_ */
