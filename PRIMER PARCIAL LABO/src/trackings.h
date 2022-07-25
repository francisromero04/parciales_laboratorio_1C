#ifndef TRACKINGS_H_
#define TRACKINGS_H_

#include "utn.h"

#define LIBRE 0
#define BAJA -1
#define EN_VIAJE 3
#define ENTREGADO 1

typedef struct
{
	int idTrack;
	int FK_idProducto;
	int FK_idComprador;
	int FK_idVendedor;
	int isEmpty;
	int cantidad;
	int distanciaKm;
	long int horaLlegada;
}sTrack;

//PROTOTIPOS ABM
int sTrack_addTracks(sTrack trackings[], int TAM_T, int idProducto, int cantidad, int codigoPostal);
int sTrack_removeTracks(sTrack array[], int TAM);
int sTrack_modifyData(sTrack array[], int TAM);
void sTrack_initTracks(sTrack array[], int TAM);
int sTrack_printTracks(sTrack array[], int TAM_U);
int sTrack_login(sTrack array[], int TAM_U);
int sTrack_CargaForzada(sTrack array[]);
int sTrack_actualizarEstado(sTrack trackings[], int TAM);
sTrack sTrack_CalcularHora(int idProducto, int cantidad, int codigoPostal);
int sTracks_FindByUserID(sTrack array[], int TAM, int idUsuario);

#endif /* TRACKINGS_H_ */
