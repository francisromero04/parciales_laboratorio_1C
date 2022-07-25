#include "relations.h"

//------------------------------------------------------STATICS HEADERS----------------------------------------------------------------------------

static int Relations_BuyProduct(sUsers usuarios[], int TAM_U, sProducts productos[], int TAM_P, sTrack trackings[], int TAM_T, int sesionIniciada);
static int Relations_SellProduct(sUsers usuarios[], int TAM_U, sProducts productos[], int TAM_P, int sesionIniciada);
static void Relations_PrintPurchase(sTrack tracking, sProducts producto);
static int Relations_PrintPurchases(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P, int idUsuario);
static int Relations_PurchasesStatus(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P, int idUsuario);
static int Relations_PrintSellings(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P, int idUsuario);
static int Relations_SellingsMades(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P, int idUsuario);
static int Relations_SellingsStatus(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P, sUsers usuarios[], int TAM_U, int idUsuario);
static int Relations_PrintGlobalTrackings(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P);
static void Relations_PrintTrackings(sTrack tracking, sProducts producto);
static int Relations_UserMenu(sUsers usuarios[], int TAM_U, sProducts productos[], int TAM_P, sTrack trackings[], int TAM_T, int sesionIniciada);
static int Relations_AdminMenu(sUsers usuarios[], int TAM_U, sProducts productos[], int TAM_P, sTrack trackings[], int TAM_T);

//-----------------------------------------------------USER MENU FUNCTIONS------------------------------------------------------------------------

static int Relations_BuyProduct(sUsers usuarios[], int TAM_U, sProducts productos[], int TAM_P, sTrack trackings[], int TAM_T, int sesionIniciada)
{
	int rtn = -1;
	int indexProd;
	int trackingIndex;
	int cantidadRequerida;
	int precioTotal;

	if(trackings != NULL && productos != NULL && usuarios != NULL && TAM_P > 0 && TAM_T > 0 && TAM_U > 0)
	{
		indexProd = sProducts_BuyProduct(productos, TAM_P);
		utn_getNumero("INGRESE CANTIDAD REQUERIDA DEL PRODUCTO: ", "ERROR. ", 1, 100, 2, &cantidadRequerida);
		productos[indexProd].stockDisponible -= cantidadRequerida;
		precioTotal = productos[indexProd].precio * cantidadRequerida;
		printf("PRECIO A PAGAR: $%d \n", precioTotal);
		trackingIndex = sTrack_addTracks(trackings, TAM_T, productos[indexProd].idProducto,
				        cantidadRequerida, usuarios[sesionIniciada].codigoPostal);
		trackings[trackingIndex].FK_idComprador = usuarios[sesionIniciada].idUsuario;
	}

	return rtn;
}

static int Relations_PurchasesStatus(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P, int idUsuario)
{
	int rtn = -1;
	int opcion;
	int indexUser;

	if(trackings != NULL && TAM_T > 0 && productos != NULL && TAM_P > 0)
	{
		indexUser = sTracks_FindByUserID(trackings, TAM_T, idUsuario);

		if(indexUser != -1)
		{
			sTrack_actualizarEstado(trackings, TAM_T);
			Relations_PrintPurchases(trackings, TAM_T, productos, TAM_P, idUsuario);

			do
			{
				puts("\nOPCIONES ESTADO DE COMPRAS");
				puts("\t1) CANCELAR COMPRA");
				puts("\t2) VOLVER AL MENU DE USUARIO");

				utn_getNumero("ELIJA UNA OPCION A REALIZAR: ", "ERROR. ", 1, 2, 2, &opcion);

				if(opcion == 1)
				{
					sTrack_removeTracks(trackings, TAM_T);
				}

			}while(opcion != 2);
		}
		else
		{
			puts("\nNO HAY COMPRAS REGISTRADAS.");
		}
	}

	return rtn;
}

static void Relations_PrintPurchase(sTrack tracking, sProducts producto)
{
	char estadoTracking[TAM_CHAR];

	//IMPRIME TODA LA INFO DE LA COMPRA DEL PRODUCTO Y SU TRACKING
	printf("|%-4d|%-16s|", tracking.idTrack, producto.nombreProducto);

	switch(tracking.isEmpty)
	{
		case EN_VIAJE:
			strncpy(estadoTracking, "EN VIAJE", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;

		case ENTREGADO:
			strncpy(estadoTracking, "ENTREGADO", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;

		case BAJA:
			strncpy(estadoTracking, "CANCELADO", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;
	}
}

static int Relations_PrintPurchases(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P, int idUsuario)
{
	int rtn = -1;
	int i;
	int idProd;
	int indexId;

	if(trackings != NULL && productos != NULL && TAM_P > 0 && TAM_T > 0)
	{
		puts("\n\tLISTADO DE COMPRAS");
		puts("+--------------------------------------+");
		puts("| ID |    PRODUCTO    |     ESTADO     |");
		puts("+--------------------------------------+");

		for(i = 0; i < TAM_T; i++)
		{
			if(trackings[i].FK_idComprador == idUsuario)
			{
				idProd = trackings[i].FK_idProducto;//FIND THE PRODUCT INDEX OF THE ID
				indexId = sProducts_findProductsByID(productos, TAM_P, idProd);
				Relations_PrintPurchase(trackings[i], productos[indexId]);
				rtn = 1;
			}
		}
	}

	return rtn;
}

static int Relations_SellProduct(sUsers usuarios[], int TAM_U, sProducts productos[], int TAM_P, int sesionIniciada)
{
	int rtn = -1;
	int indexProd;

	if(usuarios != NULL && productos != NULL)
		{
			if(TAM_U > 0 && TAM_P > 0)
			{
				if(sesionIniciada != -1)
				{
					indexProd = sProducts_addProducts(productos, TAM_P);
					productos[indexProd].FK_idVendedor = usuarios[sesionIniciada].idUsuario;
					rtn = 1;
				}
			}
		}

	return rtn;
}

static int Relations_PrintSellings(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P, int idUsuario)
{
	int i;
	int j;
	int rtn = -1;

	if (trackings != NULL && TAM_T > 0 && productos != NULL && TAM_P > 0)
	{
		for(i = 0; i < TAM_P; i++)
		{
			if(productos[i].FK_idVendedor == idUsuario)
			{
				for(j = 0; j < TAM_T; i++)
				{
					if(trackings[j].FK_idProducto == productos[i].idProducto)
					{
						if(trackings[j].isEmpty == EN_VIAJE || trackings[j].isEmpty == ENTREGADO || trackings[j].isEmpty == BAJA)
						{
							Relations_PrintPurchase(trackings[j], productos[i]);
						}
					}
				}
			}
		}
	}


	return rtn;
}

static int Relations_SellingsMades(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P, int idUsuario)
{

	int rtn = -1;
	int i;
	int j;
	int index;

	if (productos != NULL && trackings != NULL)
	{
		if (TAM_T > 0 && TAM_P > 0)
		{
			for (i = 0; i < TAM_P; i++)
			{
				if(productos[i].FK_idVendedor == idUsuario)
				{
					index = sProducts_findProductsByID(productos, TAM_P, productos[i].idProducto);

					for(j = 0; j < TAM_T; j++)
					{
						if(trackings[j].FK_idProducto == productos[index].idProducto)
						{
							if(trackings[j].isEmpty == ENTREGADO || trackings[j].isEmpty == BAJA || trackings[j].isEmpty == EN_VIAJE)
							{
								rtn = 1;
							}
						}
					}
				}
			}
		}
	}

	return rtn;
}

static int Relations_SellingsStatus(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P, sUsers usuarios[], int TAM_U, int idUsuario)
{
	int rtn = -1;

	if(trackings != NULL && TAM_T > 0)
	{
		sTrack_actualizarEstado(trackings, TAM_T);
		if(Relations_SellingsMades(trackings, TAM_T, productos, TAM_P, idUsuario) == 1)
		{
			puts("\n\tLISTADO DE VENTAS");
			puts("+--------------------------------------+");
			puts("| ID |    PRODUCTO    |     ESTADO     |");
			puts("+--------------------------------------+");
			Relations_PrintSellings(trackings, TAM_T, productos, TAM_P, idUsuario);
			rtn = 1;
		}
		else
		{
			puts("\nNO HAY VENTAS REGISTRADAS");
		}
	}

	return rtn;
}

//-----------------------------------------------------ADMIN MENU FUNCTIONS------------------------------------------------------------------------

static void Relations_PrintTrackings(sTrack tracking, sProducts producto)
{
	char estadoTracking[TAM_CHAR];

	puts("\n\t\t\tTRACKING GLOBAL");
	puts("+--------------------------------------------------------------------------------------+");
	puts("|   ID TRACKING  |   ID VENDEDOR  |  ID COMPRADOR  | NOMBRE  PRODUCTO |     ESTADO     |");
	puts("+--------------------------------------------------------------------------------------+");

	printf("|%-16d|%-16d|%-16d|%-18s|", tracking.idTrack, producto.FK_idVendedor, tracking.FK_idComprador, producto.nombreProducto);

	switch(tracking.isEmpty)
	{
		case EN_VIAJE:
			strncpy(estadoTracking, "EN VIAJE", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;

		case ENTREGADO:
			strncpy(estadoTracking, "ENTREGADO", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;

		case BAJA:
			strncpy(estadoTracking, "CANCELADO", sizeof(estadoTracking));
			printf("%-16s|\n", estadoTracking);
		break;
	}
	puts("+--------------------------------------------------------------------------------------+");
}

static int Relations_PrintGlobalTrackings(sTrack trackings[], int TAM_T, sProducts productos[], int TAM_P)
{
	int i;
	int rtn = -1;
	int indexProd;

	if (trackings != NULL && TAM_T > 0)
	{
		for (i = 0; i < TAM_T; i++)
		{
			if(trackings[i].isEmpty != LIBRE)
			{
				indexProd = sProducts_findProductsByID(productos, TAM_P, trackings[i].FK_idProducto);

				if(indexProd != -1)
				{
					sTrack_actualizarEstado(trackings, TAM_T);
					Relations_PrintTrackings(trackings[i], productos[indexProd]);
					break;
					rtn = 1;
				}
			}
			else
			{
				puts("\nTRACKING GLOBAL SIN COMPRAS REGISTRADAS.");
				break;
			}
		}
	}


	return rtn;
}

//------------------------------------------------------MENU FUNCTIONS-----------------------------------------------------------------------------

static int Relations_UserMenu(sUsers usuarios[], int TAM_U, sProducts productos[], int TAM_P, sTrack trackings[], int TAM_T, int sesionIniciada)
{
	int opcion;
	int rtn = -1;

	if(usuarios != NULL && productos != NULL && trackings != NULL && TAM_U > 0 && TAM_P > 0 && TAM_T > 0)
	{
		do
		{
			puts("\n\n\t\t\t\t\t*********************************");
			puts("\t\t\t\t\t****** 1er EXAM LAB I - 1H ******");
			puts("\t\t\t\t\t*********** USUARIO *************");
			puts("\t\t\t\t\t*********************************\n");
			puts("1) COMPRAR");
			puts("2) VENDER");
			puts("3) ESTADO DE COMPRAS");
			puts("4) ESTADO DE VENTAS");
			puts("5) CERRAR SESION (USUARIO)\n");

			utn_getNumero("INGRESE OPCION: ", "ERROR. ", 0, 5, 2, &opcion);

			switch(opcion)
			{
				case 1:
					Relations_BuyProduct(usuarios, TAM_U, productos, TAM_P, trackings, TAM_T, sesionIniciada);
				break;

				case 2:
					Relations_SellProduct(usuarios, TAM_U, productos, TAM_P, sesionIniciada);
				break;

				case 3:
					Relations_PurchasesStatus(trackings, TAM_T, productos, TAM_P, usuarios[sesionIniciada].idUsuario);
				break;

				case 4:
					Relations_SellingsStatus(trackings, TAM_T, productos, TAM_P, usuarios, TAM_U, usuarios[sesionIniciada].idUsuario);
				break;
			}
		}while(opcion != 5);
	}
	else
	{
		rtn = 0; //ERROR ARRAYS NULOS
	}

	return rtn;
}

static int Relations_AdminMenu(sUsers usuarios[], int TAM_U, sProducts productos[], int TAM_P, sTrack trackings[], int TAM_T)
{
	int rtn = -1;
	int opcion;

	if(trackings != NULL && productos != NULL && usuarios != NULL && TAM_T > 0 && TAM_P > 0 && TAM_U > 0)
	{
		do{
			puts("\n\t\t\t\t\t*********************************");
			puts("\t\t\t\t\t****** 1er EXAM LAB I - 1H ******");
			puts("\t\t\t\t\t************* ADMIN *************");
			puts("\t\t\t\t\t*********************************\n");
			puts("\tGESTION E INFORMES");
			puts("1) LISTAR ESTADO DE TODOS LOS USUARIOS");
			puts("2) LISTAR TODOS LOS PRODUCTOS POR CATEGORIA");
			puts("3) BAJA DE UN PRODUCTO");
			puts("4) BAJA DE UN USUARIO");
			puts("5) VER TRACKING GLOBAL");
			puts("6) CERRAR SESION (ADMIN)");

			utn_getNumero("\nINGRESE OPCION: ", "ERROR. ", 1, 6, 2, &opcion);

			switch(opcion)
			{
				case 1:
					sUsers_printUsers(usuarios, TAM_U);
				break;

				case 2:
					sProducts_sortProducts(productos, TAM_P);
					puts("\n\t\t LISTA DE PRODUCTOS");
					puts("+----------------------------------------------------------------+");
					puts("| ID |     NOMBRE     |   STOCK  |   PRECIO   |     CATEGORIA    |");
					puts("+----------------------------------------------------------------+");
					sProducts_printProducts(productos, TAM_P);
				break;

				case 3:
					puts("\n\t\t LISTA DE PRODUCTOS");
					puts("+----------------------------------------------------------------+");
					puts("| ID |     NOMBRE     |   STOCK  |   PRECIO   |     CATEGORIA    |");
					puts("+----------------------------------------------------------------+");
					sProducts_removeProducts(productos, TAM_P);
				break;

				case 4:
					sUsers_removeUsers(usuarios, TAM_U);
				break;

				case 5:
					Relations_PrintGlobalTrackings(trackings, TAM_T, productos, TAM_P);
				break;
			}

		} while(opcion != 6);

		rtn = 1;
	}

	return rtn;
}

int Relations_TypesMenu(sUsers usuarios[], int TAM_U, sProducts productos[], int TAM_P, sTrack trackings[], int TAM_T)
{
	int rtn = -1;
	int sesionIniciada;

	if(trackings != NULL && productos != NULL && usuarios != NULL && TAM_P > 0 && TAM_T > 0 && TAM_U > 0)
	{
		sesionIniciada = sUsers_login(usuarios, TAM_U);

		if(usuarios[sesionIniciada].tipo == USUARIO)
		{
			Relations_UserMenu(usuarios, TAM_U, productos, TAM_P, trackings, TAM_T, sesionIniciada);
		}
		else
		{
			if(usuarios[sesionIniciada].tipo == ADMIN)
			{
				Relations_AdminMenu(usuarios, TAM_U, productos, TAM_P, trackings, TAM_T);
			}
		}
		rtn = 1;
	}

	return rtn;
}
