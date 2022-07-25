#include <stdio.h>
#include <stdlib.h>
#include "../inc/LinkedList.h"
#include "../inc/parser.h"
#include "../inc/Peliculas.h"

/** \brief Carga los datos de los Peliculas desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPeliculas LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListPeliculas)
{
	int rtn = -1;
	FILE* pFile = fopen(path, "r");

	if(pArrayListPeliculas != NULL && path != NULL)
	{
		printf("\nSE HAN CARGADO LOS DATOS DEL ARCHIVO CSV...\n");
		parser_PeliculasFromText(pFile, pArrayListPeliculas);
		parser_PeliculasFromText(pFile, pArrayListPeliculas);
		rtn = 1;
	}
	return rtn;
}

/** \brief Carga los datos de los Peliculas desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPeliculas LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListPeliculas)
{
	int rtn = -1;

	if(pArrayListPeliculas!=NULL && path!=NULL)
	{
		printf("\nSE HAN CARGADO LOS DATOS DEL ARCHIVO BIN...\n");
		FILE* pFile = fopen(path, "rb");

		if(pFile != NULL)
		{
			//parser_PeliculasFromBinary(pFile , pArrayListPeliculas);
			rtn = 1;
		}
	}
	return rtn;
}

/** \brief Listar Peliculas
 *
 * \param path char*
 * \param pArrayListPeliculas LinkedList*
 * \return int
 *
 */
int controller_ListPeliculas(LinkedList* pArrayListPeliculas)
{
	int rtn = -1;
	int lenList;

	if(pArrayListPeliculas!=NULL)
	{
		lenList = ll_len(pArrayListPeliculas);

		puts("\n\t\tLISTADO DE PELICULAS");
		puts("+-------------------------------------------------------------+");
		puts("| ID |    NOMBRE DE LA PELICULA   |     GENERO     |  RATING  |");
		puts("+-------------------------------------------------------------+");

		for (int i = 0; i < lenList; i++)
		{
			Peliculas* pPeliculas = ll_get(pArrayListPeliculas, i);
			Peliculas_imprimir(pPeliculas);
			puts("+-------------------------------------------------------------+");
		}


		rtn = 1;
	}
	return rtn;
}

/** \brief Ordenar Peliculas
 *
 * \param path char*
 * \param pArrayListPeliculas LinkedList*
 * \return int
 *
 */
int controller_sortPeliculas(LinkedList* pArrayListPeliculas)
{
	int rtn = -1;

	if(pArrayListPeliculas != NULL)
	{
		rtn = 1;
        ll_sort(pArrayListPeliculas, Pelicula_OrdenamientoPorGeneroRating, 1);
	}

    return rtn;
}

/** \brief Guarda los datos de los Peliculas en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPeliculas LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListPeliculas)
{
	int rtn = -1;
	int id;
	char titulo[30];
	float rating;
	char genero[30];

	Peliculas* Pelicula = NULL;
	FILE* pFile;

	if(path != NULL && pArrayListPeliculas != NULL)
	{
		pFile = fopen(path, "w");

		Pelicula=Peliculas_new();

		if(Pelicula != NULL)
		{
			fprintf(pFile, "id,titulo,genero,rating\n");
			for(int i = 0; i < ll_len(pArrayListPeliculas); i++)
			{
				Pelicula = (Peliculas*) ll_get(pArrayListPeliculas, i);
				if(Pelicula != NULL)
				{

					Pelicula_GetId(Pelicula, &id);
					Pelicula_GetTitulo(Pelicula, titulo);
					Pelicula_GetGenero(Pelicula, genero);
					Pelicula_GetRating(Pelicula, &rating);

					fprintf(pFile,"%d,%s,%s,%.1f\n", id, titulo, genero, rating);
					rtn = 1;
				}
				else
				{
					rtn = 0;
					break;
				}
			}
		}
		fclose(pFile);

		if(rtn)
		{
			printf("\nLA LISTA SE GUARDO CON EXITO (TXT)\n");
		}
	}

	return rtn;
}

int controller_getUltimoId()
{
	int ultimoId = 1;
	char ultimoIdStr[100];

	FILE* pFile = fopen("ultimoId.txt", "r");

	if(pFile != NULL)
	{
		fscanf(pFile, "%[^\n]", ultimoIdStr);

		ultimoId = atoi(ultimoIdStr);
	}
	else
	{
	    pFile = fopen("ultimoId.txt", "w");
	    fprintf(pFile, "%d\n", ultimoId);
	}
	fclose(pFile);

	return ultimoId;
}
