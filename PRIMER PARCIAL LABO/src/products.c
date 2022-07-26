#include "products.h"

//-----------------------------------------------------STATICS HEADERS---------------------------------------------------

static int sProducts__getID(void);
static int sProducts_getFreeIndex(sProducts array[], int TAM);
static sProducts sProducts_enterData(void);
static void sProducts_printOne(sProducts Producto);

//-----------------------------------------------------STATICS SOURCES---------------------------------------------------

/// @fn int sProducts__getID(void)
/// @brief Con la variable Products_idIncremental incrementa un ID desde 1000 en adelante
/// @return Retorna el ID que incremento
static int sProducts__getID(void)
{
	///INICIALIZADO UNA UNICA VEZ AL COMIENZO DEL PROGRAMA CON ALCANCE UNICAMENTE EN FUNCION sProducts_getID();
	static int Products_idIncremental = 1006;
	static int rtn;

	rtn = Products_idIncremental++;

	return rtn;
}

/// @fn int sProducts_getFreeIndex(sProducts[], int)
/// @brief Recibe el array cuyo tipo de dato es sProducts y su tama�o, luego busca un espacio LIBRE en el indice,
///  para despu�s guardar datos en ese espacio
/// @param array
/// @param TAM
/// @return Retorna el espacio LIBRE que encontro en el indice
static int sProducts_getFreeIndex(sProducts array[], int TAM)
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

/// @fn int sProducts_findProductsByID(sProducts[], int, int)
/// @brief Recibe el array cuyo tipo de dato es sProducts, su tama�o y el ID a buscar en el indice
/// @param array
/// @param TAM
/// @param ID
/// @return Retorna el indice en dondese ubica el ID encontrado
int sProducts_findProductsByID(sProducts array[], int TAM, int ID)
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
			if (array[i].idProducto == ID && array[i].isEmpty == OCUPADO)
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

/// @fn sProducts sProducts_enterData(void)
/// @brief Pide los datos a cargar en un auxiliar cuyo tipo de dato es sProducts,
/// para luego poder darde ALTA un Producto en sProducts_addProductss
/// @return Retorna ese auxiliar con los datos cargados
static sProducts sProducts_enterData(void)
{
	sProducts auxiliar;
	int opcionCategoria;

	printf("\n");
	utn_getString("INGRESE NOMBRE DEL PRODUCTO: ", "ERROR. ", 3, TAM_CHAR, auxiliar.nombreProducto);
	utn_getNumero("INGRESE PRECIO DEL PRODUCTO: ", "ERROR. ", 0, 999999, 3, &auxiliar.precio);
	utn_getNumero("INGRESE STOCK DISPONIBLE: ", "ERROR. ", 1, 100, 3, &auxiliar.stockDisponible);
	utn_getNumero("INGRESE CATEGORIA DEL PRODUCTO (TIPO 1: TECNOLOGIA | TIPO 2: ROPA | TIPO 3: ELECTRODOMESTICOS): ",
				"ERROR. ", 1, 3, 2, &opcionCategoria);
	switch(opcionCategoria)
	{
		case 1:
			auxiliar.categoria = TECNOLOGIA;
		break;

		case 2:
			auxiliar.categoria = ROPA;
		break;

		case 3:
			auxiliar.categoria = ELECTRODOMESTICOS;
		break;
	}

	return auxiliar;
}

int sProducts_FindByName(sProducts productos[], int TAM_U, char nombreProducto[])
{
	int i;
	int rtn = -1;

	if(productos != NULL && TAM_U > 0)
	{
		for (i = 0; i < TAM_U; i++)
		{
			if((strcmp(productos[i].nombreProducto, nombreProducto)) == 0 && productos[i].isEmpty != LIBRE)
			{
				rtn = i;
				break;
			}
		}

	}

	return rtn;
}

/// @fn void sProducts_printOne(sProducts, int)
/// @brief Recibe un tipo de dato sProducts y un criterio a mostrar. Segun el criterio, muestra
/// @param Producto
/// @param criterio
static void sProducts_printOne(sProducts Producto)
{
	char categoria[TAM_CHAR];

	printf("|%4d|%-16s|%-10d|%-12d|", Producto.idProducto, Producto.nombreProducto, Producto.stockDisponible, Producto.precio);

	switch(Producto.categoria)
	{
		case TECNOLOGIA:
			strncpy(categoria, "TECNOLOGIA", sizeof(categoria));
			printf("%-18s|\n", categoria);
		break;

		case ROPA:
			strncpy(categoria, "ROPA", sizeof(categoria));
			printf("%-18s|\n", categoria);
		break;

		case ELECTRODOMESTICOS:
			strncpy(categoria, "ELECTRODOMESTICOS", sizeof(categoria));
			printf("%-18s|\n", categoria);
		break;
	}
}

int sProducts_sortProducts(sProducts productos[], int TAM)
{
	int i;
	int j;
	int rtn = -1;
	sProducts aux;

	//SI EXISTE EL productos Y EL LIMITE ES VALIDO
	if (productos != NULL && TAM > 0)
	{
		for (i = 0; i < TAM - 1; i++)
		{
			for (j = i + 1; j < TAM; j++)
			{
				if (productos[i].isEmpty == OCUPADO && productos[j].isEmpty == OCUPADO)
				{
					if (productos[i].categoria > productos[j].categoria) //ORDENO POR CATEGORIA
					{
						//CAMBIO POSICIONES
						aux = productos[i];
						productos[i] = productos[j];
						productos[j] = aux;
					}
					else
					{
						if(productos[i].categoria == productos[j].categoria) //SI LAS CATEGORIAS SON IGUALES ORDENO POR EL NOMBRE
						{
							if(( strcmp(productos[i].nombreProducto, productos[j].nombreProducto) ) > 0) //COMPARA CADENAS PARA SABER CUAL ES MAYOR
							{
								//CAMBIO POSICIONES
								aux = productos[i];
								productos[i] = productos[j];
								productos[j] = aux;
							}
						}
					}
				}
			}
		}
	}

	return rtn;
}

int sProduct_sortProductsByStock(sProducts productos[], int TAM)
{
	int rtn = -1;
	int i;
	int j;
	sProducts aux;

	if(productos != NULL)
	{
		if(TAM > 0)
		{
			for(i = 0; i < TAM - 1; i++)
			{
				for(j = i + 1; j < TAM; j++)
				{
					if(productos[i].isEmpty && productos[j].isEmpty)
					{
						if (productos[i].stockDisponible > productos[j].stockDisponible)
						{
							aux = productos[i];
							productos[i] = productos[j];
							productos[j] = aux;
						}
					}
				}
			}
		}
	}

	return rtn;
}

//-----------------------------------------------------ABM---------------------------------------------------------------

/// @fn int sProducts_addProductss(sProducts[], int)
/// @brief Recibe el array cuyo tipo de dato es sProductsenger y su tama�o, luego busca un indice LIBRE en el array para
/// poder dar de alta. Pide los datos del Producto y le da un ID �nico a cada uno cambiandole su estado a OCUPADO
/// @param array
/// @param TAM
/// @return Retorna 1 si se pudo dar de alta o -1 si hubo algun error
int sProducts_addProducts(sProducts array[], int TAM)
{
	int rtn = -1;
	sProducts auxProducts;

	///BUSCO ESPACIO EN ARRAY
	int index = sProducts_getFreeIndex(array, TAM);

	///SI INDEX == -1 ARRAY LLENO
	///SI INDEX != -1 TENGO EN INDEX POSICION DE ARRAY LIBRE

	if (index != -1)
	{
		///PIDO DATOS - CARGO Products AUXILIAR
		auxProducts = sProducts_enterData();

		///SETEO ID UNICO - VARIABLE ESTATICA AUTOINCREMENTAL
		auxProducts.idProducto = sProducts__getID();

		///CAMBIO SU ESTADO A "OCUPADO"
		auxProducts.isEmpty = OCUPADO;

		///SETEO EL ARRAY CON AUXILIAR EN INDEX LIBRE OBTENIDO PREVIAMENTE
		array[index] = auxProducts;

		///RETORNO 1 PARA SABER QUE FUE DADO DE ALTA SATISFACTORIAMENTE
		rtn = index;
	}

	return rtn;
}

int sProducts_verifyUserProducts(sProducts productos[], int TAM, int idUsuario)
{
	int rtn = -1;
	int i;

	if (productos != NULL)
	{
		if (TAM > 0 && idUsuario > 0)
		{
			for (i = 0; i < TAM; i++)
			{	//LISTS EVERY PRODUCT WITH STATUS GIVEN
				if(productos[i].FK_idVendedor == idUsuario)
				{
					if (productos[i].isEmpty == OCUPADO)
					{
						rtn = 1;
					}
				}
			}
		}
	}
	return rtn;
}

int sProducts_ReplaceStock(sProducts productos[], int TAM, int idUsuario)
{
	int rtn = -1;
	int indexProd;
	int id;
	int nuevoStock;

	if (productos != NULL)
	{
		if (TAM > 0 && idUsuario > 0)
		{
			if(sProducts_verifyUserProducts(productos, TAM, idUsuario) == 1)
			{
				sProducts_printUserProducts(productos, TAM, idUsuario);
				utn_getNumero("\nINGRESE ID DEL PRODUCTO: ", "ERROR. ", 1000, 9999, 3, &id);
				indexProd = sProducts_findProductsByID(productos, TAM, id);

				if(indexProd != -1)
				{
					utn_getNumero("INGRESE STOCK A REPONER: ", "ERROR. ", 1, 200, 3, &nuevoStock);
					productos[indexProd].stockDisponible += nuevoStock;
					puts("\nSTOCK ACTUALIZADO EXITOSAMENTE.");
					rtn = 1;
				}
			}
			else
			{
				puts("\nUSTED NO TIENE PRODUCTOS A LA VENTA PARA REPONER STOCK.");
			}
		}
	}

	return rtn;
}

int sProducts_BuyProduct(sProducts productos[], int TAM)
{
	int rtn = -1;
	int idProducto;
	int indexProd;

	if(productos != NULL && TAM > 0)
	{
		sProducts_printProducts(productos, TAM);
		utn_getNumero("\nINGRESE ID DEL PRODUCTO A COMPRAR: ", "ERROR. ", 1000, 9999, 2, &idProducto);

		indexProd = sProducts_findProductsByID(productos, TAM, idProducto);

		if(indexProd != -1)
		{
			productos[indexProd].idProducto = idProducto;
			printf("PRODUCTO COMPRADO: %s \n", productos[indexProd].nombreProducto);

			while(productos[indexProd].stockDisponible == 0)
			{
				utn_getNumero("PRODUCTO SIN STOCK, INGRESE OTRO ID: ", "ERROR. ", 1000, 9999, 2, &idProducto);
				indexProd = sProducts_findProductsByID(productos, TAM, idProducto);
			}
			rtn = indexProd;
		}
		else
		{
			puts("\nEL PRODUCTO QUE USTED REQUIERE COMPRAR NO EXISTE.");
		}
	}

	return rtn;
}

/// @fn int sProducts_removeProductss(sProducts[], int)
/// @brief Recibe el array cuyo tipo de dato es sProductsenger y su tama�o, muestra un listado de
/// Products donde se encuentran todos los datos de cada uno, pide el ID a dar de baja y
/// le cambia su estado a BAJA
/// @param array
/// @param TAM
/// @return Retorna 1 si se pudo dar de baja o -1 si hubo algun error
int sProducts_removeProducts(sProducts array[], int TAM)
{
	int rtn = 0;
	int idProducto;
	int index;
	int flag = 0;

	///LISTO TODOS LOS Products
	if(sProducts_printProducts(array, TAM))
	{
		///BANDERA EN 1 SI HAY Products DADOS DE ALTA PARA LISTAR
		flag = 1;
	}

	///SI HAY Products PARA DAR DE BAJA
	if(flag)
	{
		///PIDO ID A DAR DE BAJA
		utn_getNumero("\nINGRESE ID DEL PRODUCTO A DAR DE BAJA: ", "ERROR. ", 1000, 9999, 3, &idProducto);

		///BUSCO INDEX POR ID EN ARRAY
		while (sProducts_findProductsByID(array, TAM, idProducto) == -1)
		{
			puts("\nNO EXISTE ID.");

			///PIDO OTRA VEZ ID A DAR DE BAJA
			utn_getNumero("\nINGRESE ID DEL PRODUCTO A DAR DE BAJA: ", "ERROR. ", 1000, 9999, 3, &idProducto);
		}

		///OBTENGO INDEX DEL ARRAY DE Products A DAR DE BAJA
		index = sProducts_findProductsByID(array, TAM, idProducto);

		///BAJA ACEPTADA - CAMBIO ESTADO A "BAJA"
		array[index].isEmpty = BAJA;

		puts("\nSE HA DADO DE BAJA EL PRODUCTO. \n");

		///RETORNO 1 SI SE DIO DE BAJA CORRECTAMENTE
		rtn = 1;
	}

	return rtn;
}

/// @fn void sProducts_initProducts(sProducts[], int)
/// @brief Recibe el array cuyo tipo de dato es sProducts y su tamaño, para asi darle un indice LIBRE
/// @param array
/// @param TAM
void sProducts_initProducts(sProducts array[], int TAM)
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

///  @fn int sProducts_printProducts(sProducts[], int, int)
/// @brief Recibe el array cuyo tipo de dato es sProductsenger, su tama�o y el criterio el cual mostrar.
///	Luego ordena y muestra seg�n el criterio elegido.
/// @param Products
/// @param TAM
/// @param criterio
/// @return Retorna 1 si salio como se esperaba o -1 si hubo un error
int sProducts_printProducts(sProducts Products[], int TAM)
{
	int i;
	int rtn = 0;
	int cantidad = 0;

	///SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (Products != NULL && TAM > 0)
	{
		puts("\n\t\t LISTA DE PRODUCTOS");
		puts("+----------------------------------------------------------------+");
		puts("| ID |     NOMBRE     |   STOCK  |   PRECIO   |     CATEGORIA    |");
		puts("+----------------------------------------------------------------+");

		///RECORRO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			///PREGUNTO POR SU ESTADO "OCUPADO"
			if (Products[i].isEmpty == OCUPADO)
			{
				///ORDENO ALFABETICAMENTE
				///IMPRIMO UN SOLO Producto
				sProducts_sortProducts(Products, TAM);
				sProducts_printOne(Products[i]);
				puts("+----------------------------------------------------------------+");
				///CONTADOR DE Products
				cantidad++;
			}
		}
	}

	///SI CANTIDAD == 0 - NO HUBO Products PARA MOSTRAR (ARRAY SIN ALTAS)
	if (cantidad > 0)
	{
		rtn = 1;
	}

	return rtn;
}

int sProducts_printUserProducts(sProducts Products[], int TAM, int idUsuario)
{
	int i;
	int rtn = 0;
	int cantidad = 0;

	///SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (Products != NULL && TAM > 0)
	{
		puts("\n\t\t LISTA DE PRODUCTOS");
		puts("+----------------------------------------------------------------+");
		puts("| ID |     NOMBRE     |   STOCK  |   PRECIO   |     CATEGORIA    |");
		puts("+----------------------------------------------------------------+");

		///RECORRO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			if(Products[i].FK_idVendedor == idUsuario)
			{
				if (Products[i].isEmpty == OCUPADO)
				{
					sProducts_printOne(Products[i]);
					puts("+----------------------------------------------------------------+");
					cantidad++;
				}
			}
		}
	}

	///SI CANTIDAD == 0 - NO HUBO Products PARA MOSTRAR (ARRAY SIN ALTAS)
	if (cantidad > 0)
	{
		rtn = 1;
	}

	return rtn;
}

int sProducts_printFindProductsByName(sProducts productos[], int TAM, char nombre[])
{
	int i;
	int rtn = -1;

	///SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (productos != NULL && TAM > 0)
	{
		puts("\n\t\t LISTA DE PRODUCTOS");
		puts("+----------------------------------------------------------------+");
		puts("| ID |     NOMBRE     |   STOCK  |   PRECIO   |     CATEGORIA    |");
		puts("+----------------------------------------------------------------+");
		sProduct_sortProductsByStock(productos, TAM);

		///RECORRO EL ARRAY
		for (i = 0; i < TAM; i++)
		{
			if(productos[i].isEmpty == OCUPADO)
			{
				if(strcmp(productos[i].nombreProducto, nombre) == 0)
				{
					sProducts_printOne(productos[i]);
					puts("+----------------------------------------------------------------+");
					rtn = 1;
				}
			}
		}
	}

	return rtn;
}

int sProducts_CargaForzada(sProducts productos[])
{
	int rtn = -1;

	if(productos != NULL)
	{
		productos[0].precio = 2500;
		productos[0].idProducto = 1000;
		productos[0].FK_idVendedor = 100;
		productos[0].isEmpty = OCUPADO;
		productos[0].stockDisponible = 50;
		productos[0].categoria = TECNOLOGIA;
		strcpy(productos[0].nombreProducto, "Mouse Logitech");

		productos[1].precio = 25000;
		productos[1].categoria = ROPA;
		productos[1].isEmpty = OCUPADO;
		productos[1].idProducto = 1001;
		productos[1].FK_idVendedor = 100;
		productos[1].stockDisponible = 70;
		strcpy(productos[1].nombreProducto, "Puffer Polo");

		productos[2].precio = 20000;
		productos[2].idProducto = 1002;
		productos[2].isEmpty = OCUPADO;
		productos[2].FK_idVendedor = 100;
		productos[2].stockDisponible = 60;
		productos[2].categoria = ELECTRODOMESTICOS;
		strcpy(productos[2].nombreProducto, "Lavavajillas");

		productos[3].precio = 23000;
		productos[3].categoria = ROPA;
		productos[3].idProducto = 1003;
		productos[3].isEmpty = OCUPADO;
		productos[3].FK_idVendedor = 100;
		productos[3].stockDisponible = 25;
		strcpy(productos[3].nombreProducto, "Nike Blazer");

		productos[4].precio = 2000;
		productos[4].idProducto = 1004;
		productos[4].isEmpty = OCUPADO;
		productos[4].FK_idVendedor = 100;
		productos[4].stockDisponible = 85;
		productos[4].categoria = ELECTRODOMESTICOS;
		strcpy(productos[4].nombreProducto, "Microondas");

		productos[5].isEmpty = OCUPADO;
		productos[5].categoria = TECNOLOGIA;
		productos[5].precio = 50000;
		productos[5].idProducto = 1005;
		productos[5].FK_idVendedor = 100;
		productos[5].stockDisponible = 100;
		strcpy(productos[5].nombreProducto, "Tv Samsung");

		rtn = 1;
	}

	return rtn;
}




