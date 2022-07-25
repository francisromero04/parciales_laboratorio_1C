#ifndef USERS_H_
#define USERS_H_

#include "utn.h"

#define ADMIN 1
#define USUARIO 2

#define LIBRE 0
#define OCUPADO 1
#define BAJA -1

typedef struct
{
	int idUsuario;
	int isEmpty;
	int tipo;
	char email[MAX_LEN_EMAIL];
	char password[MAX_LEN_PASSWORD];
	char direccion[MAX_LEN_DIRECTION];
	int codigoPostal;
}sUsers;

//PROTOTIPOS ABM
int sUsers_addUsers(sUsers array[], int TAM);
int sUsers_removeUsers(sUsers array[], int TAM);
int sUsers_modifyData(sUsers array[], int TAM);
void sUsers_initUsers(sUsers array[], int TAM);
int sUsers_printUsers(sUsers usuarios[], int TAM_U);
int sUsers_login(sUsers usuarios[], int TAM_U);
int sUsers_CargaForzada(sUsers listaUsers[]);

#endif /* USERS_H_ */
