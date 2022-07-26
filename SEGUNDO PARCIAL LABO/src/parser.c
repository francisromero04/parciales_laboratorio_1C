#include <stdio.h>
#include <stdlib.h>
#include "../inc/LinkedList.h"
#include "../inc/parser.h"
#include "../inc/Peliculas.h"
#include "../inc/Controller.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPeliculas LinkedList*
 * \return int
 *
 */
int parser_PeliculasFromText(FILE* pFile, LinkedList* pArrayListPeliculas)
{
	int rtn = -1;
	Peliculas* auxPeliculas;
	int contadorIdIncialLista = controller_getUltimoId();
	char buffer[4][50];
	int aux;

	if(pFile != NULL && pArrayListPeliculas != NULL)
	{
		fscanf(pFile,"%[^,], %[^,], %[^,], %[^\n]\n",buffer[0], buffer[1], buffer[2], buffer[3]);

		while(!feof(pFile))
		{
			aux = fscanf(pFile,"%[^,], %[^,], %[^,], %[^\n]\n",buffer[0], buffer[1], buffer[2], buffer[3]);
			if(aux == 4)
			{
				auxPeliculas = new_PeliculasConParametros(buffer[0], buffer[1], buffer[2], buffer[3]);

				if(auxPeliculas != NULL)
				{

					auxPeliculas->id=contadorIdIncialLista;
					contadorIdIncialLista++;
					aux = ll_add(pArrayListPeliculas, auxPeliculas);

					if(aux != 0)
					{
						Peliculas_delete(auxPeliculas);
						break;
					}
					else
					{
						rtn = 1;
					}
				}
			}
			else
			{
				break;
			}
		}
		Peliculas_actualizarUltimoId(contadorIdIncialLista-1);
	}
	return rtn;
}
