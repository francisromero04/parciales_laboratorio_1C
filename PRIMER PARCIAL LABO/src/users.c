#include "users.h"

//-----------------------------------------------------STATICS HEADERS---------------------------------------------------

static int sUsers__getID(void);
static int sUsers_getFreeIndex(sUsers array[], int TAM);
static int sUsers_findUsersByID(sUsers array[], int TAM, int ID);
static sUsers sUsers_enterData(void);
static void sUsers_printOne(sUsers User);
static int sUsers_findByEmail(sUsers usuarios[], int TAM_U, char correoIngresado[]);

//-----------------------------------------------------STATICS SOURCES---------------------------------------------------

/// @fn int sUsers__getID(void)
/// @brief Con la variable users_idIncremental incrementa un ID desde 1000 en adelante
/// @return Retorna el ID que incremento
static int sUsers__getID(void)
{
	///INICIALIZADO UNA UNICA VEZ AL COMIENZO DEL PROGRAMA CON ALCANCE UNICAMENTE EN FUNCION sUsers_getID();
	static int users_idIncremental = 103;
	static int rtn;

	rtn = users_idIncremental++;

	return rtn;
}

/// @fn int sUsers_getFreeIndex(sUsers[], int)
/// @brief Recibe el array cuyo tipo de dato es sUsers y su tamaño, luego busca un espacio LIBRE en el indice,
///  para despu�s guardar datos en ese espacio
/// @param array
/// @param TAM
/// @return Retorna el espacio LIBRE que encontro en el indice
static int sUsers_getFreeIndex(sUsers array[], int TAM)
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

/// @fn int sUsers_findUsersByID(sUsers[], int, int)
/// @brief Recibe el array cuyo tipo de dato es sUsers, su tama�o y el ID a buscar en el indice
/// @param array
/// @param TAM
/// @param ID
/// @return Retorna el indice en dondese ubica el ID encontrado
static int sUsers_findUsersByID(sUsers array[], int TAM, int ID)
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
			if (array[i].idUsuario == ID && array[i].isEmpty == OCUPADO)
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

/// @fn sUsers sUsers_enterData(void)
/// @brief Pide los datos a cargar en un auxiliar cuyo tipo de dato es sUsers,
/// para luego poder darde ALTA un User en sUsers_adduserss
/// @return Retorna ese auxiliar con los datos cargados
static sUsers sUsers_enterData(void)
{
	sUsers auxiliar;

	printf("\n");
	utn_getEmail("INGRESE SU CORREO ELECTRONICO A REGISTRAR: ", "ERROR. ", 3, auxiliar.email);
	utn_getPassword("INGRESE PASSWORD A REGISTRAR (min. 4 / max. 10): ", "ERROR. ", MIN_LEN_PASSWORD, MAX_LEN_PASSWORD, 3, auxiliar.password);
	utn_getAlfaNum("INGRESE SU DOMICILIO A REGISTRAR: ", "ERROR. ", 3, MAX_LEN_DIRECTION, auxiliar.direccion);
	utn_getNumero("INGRESE CODIGO POSTAL A REGISTRAR: ", "ERROR. ", 0, 9999, 3, &auxiliar.codigoPostal);

	return auxiliar;
}

static void sUsers_printOne(sUsers User)
{
	char estadoUsuario[25];

	printf("|%4d|%-25s|", User.idUsuario, User.email);

	switch(User.tipo)
	{
		case ADMIN:
			strncpy(estadoUsuario, "ADMIN", sizeof(estadoUsuario));
			printf("%-16s|\n", estadoUsuario);
		break;

		case USUARIO:
			strncpy(estadoUsuario, "USUARIO", sizeof(estadoUsuario));
			printf("%-16s|\n", estadoUsuario);
		break;
	}
}

static int sUsers_findByEmail(sUsers usuarios[], int TAM_U, char correoIngresado[])
{
	int i;
	int rtn = -1;

	if(usuarios != NULL && TAM_U > 0)
	{
		for (i = 0; i < TAM_U; i++)
		{
			if((strcmp(usuarios[i].email, correoIngresado)) == 0 && usuarios[i].isEmpty != LIBRE)
			{
				rtn = i;
				break;
			}
		}

	}

	return rtn;
}

//-----------------------------------------------------ABM---------------------------------------------------------------

/// @fn int sUsers_adduserss(sUsers[], int)
/// @brief Recibe el array cuyo tipo de dato es sUsersenger y su tama�o, luego busca un indice LIBRE en el array para
/// poder dar de alta. Pide los datos del User y le da un ID �nico a cada uno cambiandole su estado a OCUPADO
/// @param array
/// @param TAM
/// @return Retorna 1 si se pudo dar de alta o -1 si hubo algun error
int sUsers_addUsers(sUsers array[], int TAM)
{
	int rtn = -1;
	sUsers auxusers;

	///BUSCO ESPACIO EN ARRAY
	int index = sUsers_getFreeIndex(array, TAM);

	///SI INDEX == -1 ARRAY LLENO
	///SI INDEX != -1 TENGO EN INDEX POSICION DE ARRAY LIBRE

	if (index != -1)
	{
		///PIDO DATOS - CARGO users AUXILIAR
		auxusers = sUsers_enterData();

		///SETEO ID UNICO - VARIABLE ESTATICA AUTOINCREMENTAL
		auxusers.idUsuario = sUsers__getID();

		///CAMBIO SU ESTADO A "OCUPADO"
		auxusers.isEmpty = OCUPADO;
		auxusers.tipo = USUARIO;

		///SETEO EL ARRAY CON AUXILIAR EN INDEX LIBRE OBTENIDO PREVIAMENTE
		array[index] = auxusers;

		///RETORNO 1 PARA SABER QUE FUE DADO DE ALTA SATISFACTORIAMENTE
		rtn = 1;
	}

	return rtn;
}

/// @fn int sUsers_removeuserss(sUsers[], int)
/// @brief Recibe el array cuyo tipo de dato es sUsersenger y su tama�o, muestra un listado de
/// users donde se encuentran todos los datos de cada uno, pide el ID a dar de baja y
/// le cambia su estado a BAJA
/// @param array
/// @param TAM
/// @return Retorna 1 si se pudo dar de baja o -1 si hubo algun error
int sUsers_removeUsers(sUsers array[], int TAM)
{
	int rtn = 0;
	int idUser;
	int index;
	int flag = 0;

	///LISTO TODOS LOS users
	if(sUsers_printUsers(array, TAM))
	{
		///BANDERA EN 1 SI HAY users DADOS DE ALTA PARA LISTAR
		flag = 1;
	}

	///SI HAY users PARA DAR DE BAJA
	if(flag)
	{
		///PIDO ID A DAR DE BAJA
		utn_getNumero("\nINGRESE ID DEL USUARIO A DAR DE BAJA: ", "ERROR. ", 100, 9999, 3, &idUser);

		///BUSCO INDEX POR ID EN ARRAY
		while (sUsers_findUsersByID(array, TAM, idUser) == -1)
		{
			puts("\nNO EXISTE ID.");

			///PIDO OTRA VEZ ID A DAR DE BAJA
			utn_getNumero("\nINGRESE ID DEL USUARIO A DAR DE BAJA: ", "ERROR. ", 100, 9999, 3, &idUser);
		}

		///OBTENGO INDEX DEL ARRAY DE users A DAR DE BAJA
		index = sUsers_findUsersByID(array, TAM, idUser);

		///BAJA ACEPTADA - CAMBIO ESTADO A "BAJA"
		array[index].isEmpty = BAJA;

		puts("\nSE HA DADO DE BAJA EL USUARIO. \n");

		///RETORNO 1 SI SE DIO DE BAJA CORRECTAMENTE
		rtn = 1;
	}

	return rtn;
}

/// @fn void sUsers_initusers(sUsers[], int)
/// @brief Recibe el array cuyo tipo de dato es sUsers y su tamaño, para asi darle un indice LIBRE
/// @param array
/// @param TAM
void sUsers_initUsers(sUsers array[], int TAM)
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

int sUsers_login(sUsers usuarios[], int TAM_U)
{
	int rtn = -1;
	int indexCorreo = 0;
	char email[MAX_LEN_EMAIL];
	char password[MAX_LEN_PASSWORD];

	if(usuarios != NULL && TAM_U > 0)
	{
		utn_getEmail("\nINGRESE SU EMAIL: ", "ERROR. ", 2, email);
		indexCorreo = sUsers_findByEmail(usuarios, TAM_U, email);

		if(indexCorreo != -1)
		{
			while(usuarios[indexCorreo].isEmpty == OCUPADO)
			{
				utn_getPassword("INGRESE SU CONTRASEÑA: ", "CONTRASEÑA INCORRECTA, REINGRESE: ", 4, MAX_LEN_PASSWORD, 2, password);

				if(strcmp(usuarios[indexCorreo].password, password) == 0)
				{
					rtn = 1;
					puts("\nSE HA INICIADO SESION CORRECTAMENTE.");
					break;
				}
			}
		}
		else
		{
			puts("SU CORREO NO SE ENCUENTRA REGISTRADO. SELECCIONE LA OPCION 2 PARA REGISTRARSE.");
		}

		rtn = indexCorreo;
	}

	return rtn;
}


int sUsers_printUsers(sUsers usuarios[], int TAM_U)
{
	int i;
	int rtn = 0;
	int cantidad = 0;
	int vueltas = 0 ;

	//SI EXISTE EL ARRAY Y EL LIMITE ES VALIDO
	if (usuarios != NULL && TAM_U > 0)
	{
		//RECORRO EL ARRAY
		for (i = 0; i < TAM_U; i++)
		{
			//PREGUNTO POR SU ESTADO "OCUPADO"
			if (usuarios[i].isEmpty == OCUPADO)
			{
				vueltas++;
				if(vueltas == 1)
				{
					//CABECERA
					puts("\n+-----------------------------------------------+");
					puts("| ID |          CORREO         |     ESTADO     |");
					puts("+-----------------------------------------------+");
				}

				//IMPRIMO UN SOLO usuario
				sUsers_printOne(usuarios[i]);
				//CONTADOR DE usuarios
				cantidad++;
				puts("+-----------------------------------------------+");
			}
		}
	}

	//SI CANTIDAD == 0 - NO HUBO usuarios PARA MOSTRAR (ARRAY SIN ALTAS)
	if (cantidad > 0)
	{
		rtn = 1;
	}

	return rtn;
}


int sUsers_CargaForzada(sUsers Users[])
{
	int rtn = -1;

	if(Users != NULL)
	{
		Users[0].idUsuario = 100;
		Users[0].isEmpty = OCUPADO;
		Users[0].tipo = USUARIO;
		Users[0].codigoPostal = 2500;
		strcpy(Users[0].direccion, "Suipacha 650");
		strcpy(Users[0].password, "venta1");
		strcpy(Users[0].email, "vendedor@gmail.com");

		Users[1].idUsuario = 101;
		Users[1].isEmpty = OCUPADO;
		Users[1].tipo = ADMIN;
		Users[1].codigoPostal = 3600;
		strcpy(Users[1].direccion, "Boedo 430");
		strcpy(Users[1].password, "admin1");
		strcpy(Users[1].email, "admin@gmail.com");

		Users[2].idUsuario = 102;
		Users[2].isEmpty = OCUPADO;
		Users[2].tipo = USUARIO;
		Users[2].codigoPostal = 1822;
		strcpy(Users[2].direccion, "Madero 1768");
		strcpy(Users[2].password, "compra1");
		strcpy(Users[2].email, "comprador@gmail.com");

		rtn = 1;
	}

	return rtn;
}
