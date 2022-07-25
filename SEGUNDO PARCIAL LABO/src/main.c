#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"
#include "../inc/parser.h"
#include "../inc/Peliculas.h"
#include "../inc/Controller.h"


int main()
{
    setbuf(stdout, NULL);

    int option;
    LinkedList* listaPeliculas = ll_newLinkedList();
    LinkedList* peliculasFiltradas;
    int flagCargarTexto = 0;

    do{
    	puts("\n\t\t\tMENU DE OPCIONES:\n"
    		"\t\t\t-----------------\n\n"
    		"1. CARGAR ARCHIVO \n"
    		"2. LISTAR PELICULAS \n"
    		"3. ASIGNAR RATINGS \n"
    		"4. ASIGNAR GENEROS \n"
    		"5. FILTRAR POR GENERO (DRAMA) Y GUARDAR EN: moviesfiltradas.txt \n"
    		"6. LISTAR PELICULAS ORDENADAS POR GENERO/RATING \n"
    		"7. GUARDAR PELICULAS EN EL ARCHIVO: movies.csv (MODO TEXTO) \n"
    		"8. SALIR \n");

    	utn_getNumero("INGRESE OPCION: ", "ERROR \n", 1, 8, 2, &option);

        switch(option)
        {
            case 1:
            	if(flagCargarTexto == 0)
            	{
            		controller_loadFromText("movies.csv",listaPeliculas);
					flagCargarTexto = 1;
            	}
            	else
            	{
            		puts("\nERROR, YA SE HA CARGADO LA LISTA (TXT).\n");
            	}
            break;

            case 2:
            	if(flagCargarTexto == 1)
				{
					controller_ListPeliculas(listaPeliculas);
				}
				else
				{
					puts("\nANTES DE LISTAR PRIMERO CARGUE LOS DATOS DEL ARCHIVO.\n");
				}
            break;

            case 3:
            	if(flagCargarTexto == 1)
				{
					if(ll_map(listaPeliculas, Peliculas_mapRating))
					{
						puts("\nSE HA ASIGNADO UN RATING ALEATORIO A CADA PELICULA.");
					}
				}
				else
				{
					puts("\nANTES DE ASIGNAR UN GENERO PRIMERO CARGUE LOS DATOS DEL ARCHIVO.");
				}
            break;

            case 4:
            	if(flagCargarTexto == 1)
				{
					if(ll_map(listaPeliculas, Peliculas_mapGenero))
					{
						puts("\nSE HA ASIGNADO UN GENERO ALEATORIO A CADA PELICULA.");
					}
				}
				else
				{
					puts("\nANTES DE ASIGNAR UN GENERO PRIMERO CARGUE LOS DATOS DEL ARCHIVO.");
				}
            break;

            case 5:
            	if(flagCargarTexto == 1)
				{
					peliculasFiltradas = ll_filter(listaPeliculas, Pelicula_FiltrarDrama);
                	controller_saveAsText("moviesFiltradas.txt", peliculasFiltradas);
				}
				else
				{
					puts("\nANTES DE FILTRAR PRIMERO CARGUE LOS DATOS DEL ARCHIVO (TXT).");
				}
            break;

            case 6:
            	if(flagCargarTexto == 1)
				{
                	controller_sortPeliculas(listaPeliculas);
					controller_ListPeliculas(listaPeliculas);
				}
				else
				{
					puts("\nANTES DE ORDENAR PRIMERO CARGUE LOS DATOS DEL ARCHIVO.");
				}
            break;

            case 7:
            	if(flagCargarTexto == 1)
            	{
					controller_saveAsText("movies.csv", listaPeliculas);
            	}
            	else
            	{
					puts("\nANTES DE GUARDAR PRIMERO CARGUE LOS DATOS DEL ARCHIVO (TXT).");
            	}
           	break;

            case 8:
            	puts("\nPROGRAMA CERRADO.");
            break;
        }
    }while(option != 8);

    return EXIT_SUCCESS;
}
