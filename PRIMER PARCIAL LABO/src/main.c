#include <stdio.h>
#include <stdlib.h>
#include "relations.h"
#define TAM_ARRAY 2000

int main(void)
{
	setbuf(stdout, NULL);
	int opcion;

	sUsers usuarios[TAM_ARRAY];
	sProducts productos[TAM_ARRAY];
	sTrack trackings[TAM_ARRAY];

	sUsers_initUsers(usuarios, TAM_ARRAY);
	sProducts_initProducts(productos, TAM_ARRAY);
	sTrack_initTracks(trackings, TAM_ARRAY);

	sUsers_CargaForzada(usuarios);
	sProducts_CargaForzada(productos);

	do{
			puts("\n\t\t\t\t\t*********************************");
			puts("\t\t\t\t\t****** 1er EXAM LAB I - 1H ******");
			puts("\t\t\t\t\t*********************************\n\n");
			puts("1) INGRESAR");
			puts("2) REGISTRARSE");
			puts("3) CERRAR PROGRAMA");

			utn_getNumero("\nINGRESE OPCION: ", "ERROR. ", 0, 3, 2, &opcion);

			switch(opcion)
			{
				case 1:
					Relations_TypesMenu(usuarios, TAM_ARRAY, productos, TAM_ARRAY, trackings, TAM_ARRAY);
				break;

				case 2:
					sUsers_addUsers(usuarios, TAM_ARRAY);
				break;

				case 3:
					puts("\nPROGRAMA CERRADO.");
				break;
			}

		}while(opcion != 3);

	return EXIT_SUCCESS;
}
