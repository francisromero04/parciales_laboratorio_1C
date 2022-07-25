#include "trackings.h"

//-----------------------------------------------------STATICS HEADERS---------------------------------------------------

static int sTrack__getID(void);
static int sTrack_getFreeIndex(sTrack array[], int TAM);
static int sTrack_findTracksByID(sTrack array[], int TAM, int ID);

//-----------------------------------------------------STATICS SOURCES---------------------------------------------------

/// @fn int sTrack__getID(void)
/// @brief Con la variable Tracks_idIncremental incrementa un ID desde 1000 en adelante
/// @return Retorna el ID que incremento
static int sTrack__getID(void)
{
	///INICIALIZADO UNA UNICA VEZ AL COMIENZO DEL PROGRAMA CON ALCANCE UNICAMENTE EN FUNCION sTrack_getID();
	static int Tracks_idIncremental = 5000;
	static int rtn;

	rtn = Tracks_idIncremental++;

	return rtn;
}

/// @fn int sTrack_getFreeIndex(sTrack[], int)
/// @brief Recibe el array cuyo tipo de dato es sTrack y su tamaño, luego busca un espacio LIBRE en el indice,
///  para despu�s guardar datos en ese espacio
/// @param array
/// @param TAM
/// @return Retorna el espacio LIBRE que encontro en el indice
static int sTrack_getFreeIndex(sTrack array[], int TAM)
{
	int rtn = -1;
	int i;

	///SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			///PREGUNTA POR EL ESTADO "LIBRE"
			if (array[i].isEmpty == LIBRE)
			{
				///OBTIENE EL PRIMER INDEX DEL VECTOR "LIBRE" Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

/// @fn int sTrack_findTracksByID(sTrack[], int, int)
/// @brief Recibe el array cuyo tipo de dato es sTrack, su tama�o y el ID a buscar en el indice
/// @param array
/// @param TAM
/// @param ID
/// @return Retorna el indice en dondese ubica el ID encontrado
static int sTrack_findTracksByID(sTrack array[], int TAM, int ID)
{
	int rtn = -1;
	int i;

	///SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		///RECORRE EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			///BUSCO QUE ESTE "OCUPADO" Y QUE CONCIDA EL ID QUE ESTOY BUSCANDO
			if (array[i].idTrack == ID && array[i].isEmpty == EN_VIAJE)
			{
				///SI ENCONTRO EL ID
				///DEVUELVE EL INDEX DE DONDE ESTA EL ID BUSCADO Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

sTrack sTrack_CalcularHora(int idProducto, int cantidad, int codigoPostal)
{
	sTrack auxiliary;
	char* horaLlegada;
	long int segundosAgregados;

	if(idProducto > 0 && cantidad > 0 && codigoPostal > 0)
	{
		auxiliary.FK_idProducto = idProducto;
		auxiliary.cantidad = cantidad;

		if(codigoPostal < 9999 && codigoPostal > 8001)
		{
			auxiliary.distanciaKm = 150;
		}
		else
		{
			if(codigoPostal < 8000 && codigoPostal > 5001)
			{
				auxiliary.distanciaKm = 80;
			}
			else
			{
				if(codigoPostal < 5000 && codigoPostal > 3001)
				{
					auxiliary.distanciaKm = 50;
				}
				else
				{
					if(codigoPostal < 3000 && codigoPostal > 1001)
					{
						auxiliary.distanciaKm = 30;
					}
					else
					{
						auxiliary.distanciaKm = 20;
					}
				}
			}
		}

		segundosAgregados = auxiliary.distanciaKm / 10 * 20;
		auxiliary.horaLlegada = time_Add(segundosAgregados);
		horaLlegada = ctime(&auxiliary.horaLlegada);
		printf("SU HORA DE LLEGADA ES: %s", horaLlegada);
	}

	return auxiliary;
}

//-----------------------------------------------------ABM---------------------------------------------------------------

/// @fn int sTrack_addTrackss(sTrack[], int)
/// @brief Recibe el array cuyo tipo de dato es sTrackenger y su tama�o, luego busca un indice LIBRE en el array para
/// poder dar de alta. Pide los datos del Track y le da un ID �nico a cada uno cambiandole su estado a OCUPADO
/// @param array
/// @param TAM
/// @return Retorna 1 si se pudo dar de alta o -1 si hubo algun error
int sTrack_addTracks(sTrack trackings[], int TAM_T, int idProducto, int cantidad, int codigoPostal)
{
	int index;
	int rtn = -1;
	sTrack aux;

	//BUSCO ESPACIO EN ARRAY
	index = sTrack_getFreeIndex(trackings, TAM_T);

	//SI INDEX == -1 ARRAY LLENO
	//SI INDEX != -1 TENGO EN INDEX POSICION DE ARRAY LIBRE

	if(trackings != NULL && TAM_T)
	{
		aux = sTrack_CalcularHora(idProducto, cantidad, codigoPostal);

		//SETEO ID UNICO - VARIABLE ESTATICA AUTOINCREMENTAL
		aux.idTrack = sTrack__getID();

		printf("SE HA GENERADO UN ALTA DE TRACKING Y ESTE ID PARA PODER SEGUIR EL ESTADO DEL ENVIO: %d \n", aux.idTrack);

		//CAMBIO SU ESTADO A "EN VIAJE"
		aux.isEmpty = EN_VIAJE;

		//SETEO EL ARRAY CON AUXILIAR EN INDEX LIBRE OBTENIDO PREVIAMENTE
		trackings[index] = aux;

		rtn = index;
	}

	return rtn;
}

/// @fn int sTrack_removeTrackss(sTrack[], int)
/// @brief Recibe el array cuyo tipo de dato es sTrackenger y su tama�o, muestra un listado de
/// Tracks donde se encuentran todos los datos de cada uno, pide el ID a dar de baja y
/// le cambia su estado a BAJA
/// @param array
/// @param TAM
/// @return Retorna 1 si se pudo dar de baja o -1 si hubo algun error
int sTrack_removeTracks(sTrack trackings[], int TAM_T)
{
	int rtn = -1;
	int idTrack;
	int indexTrack;

	if(trackings != NULL)
	{
		if(TAM_T > 0)
		{
			utn_getNumero("\nINGRESE ID DEL PRODUCTO A DAR DE BAJA: ", "ERROR. ", 1000, 9999, 3, &idTrack);
			indexTrack = sTrack_findTracksByID(trackings, TAM_T, idTrack);

			while(trackings[indexTrack].isEmpty != EN_VIAJE)
			{
				utn_getNumero("\nINGRESE ID DEL PRODUCTO A DAR DE BAJA: ", "ERROR. ", 1000, 9999, 3, &idTrack);
				indexTrack = sTrack_findTracksByID(trackings, TAM_T, idTrack);
			}

			trackings[indexTrack].isEmpty = BAJA;
			puts("SU COMPRA FUE CANCELADA.");
			rtn = 1;
		}
	}

	return rtn;
}

int sTracks_FindByUserID(sTrack array[], int TAM, int idUsuario)
{
	int rtn = -1;
	int i;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			//BUSCO QUE ESTE "OCUPADO" Y QUE CONCIDA EL ID QUE ESTOY BUSCANDO
			if (array[i].FK_idComprador == idUsuario && array[i].isEmpty == EN_VIAJE)
			{
				//SI ENCONTRE EL ID
				//DEVUELVO EL INDEX DE DONDE ESTA EL ID BUSCADO Y SALGO
				rtn = i;
				break;
			}
		}
	}

	return rtn;
}

int sTrack_actualizarEstado(sTrack trackings[], int TAM)
{
	int i;
	int rtn = -1;
	long int horaActual;

	if(trackings != NULL && TAM > 0)
	{
		horaActual = time_Current();

		for(i = 0; i < TAM; i++)
		{
			if(trackings[i].isEmpty == EN_VIAJE || trackings[i].isEmpty == ENTREGADO)
			{

				if(trackings[i].horaLlegada > horaActual)
				{
					trackings[i].isEmpty = EN_VIAJE;
				}
				else
				{
					if(trackings[i].horaLlegada < horaActual)
					{
						trackings[i].isEmpty = ENTREGADO;
					}
				}
				rtn = 1;
			}
		}
	}
	else
	{
		rtn = 0;
	}

	return rtn;
}

/// @fn void sTrack_initTracks(sTrack[], int)
/// @brief Recibe el array cuyo tipo de dato es sTrack y su tamaño, para asi darle un indice LIBRE
/// @param array
/// @param TAM
void sTrack_initTracks(sTrack array[], int TAM)
{
	int i;

	///SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (array != NULL && TAM > 0)
	{
		///RECORRE EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			///SETEA ESTADO DE "LIBRE"
			array[i].isEmpty = LIBRE;
		}
	}
}

