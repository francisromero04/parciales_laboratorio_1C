#ifndef PRODUCTS_H_
#define PRODUCTS_H_

#include "utn.h"
#define TAM_CHAR 51

#define LIBRE 0
#define BAJA -1
#define OCUPADO 1 //en venta
#define VENDIDO 2

#define ROPA 3
#define TECNOLOGIA 4
#define ELECTRODOMESTICOS 5

typedef struct
{
	int idProducto;
	short int isEmpty;
	char nombreProducto[TAM_CHAR];
	int precio;
	int stockDisponible;
	int categoria;
	int FK_idVendedor;
	int FK_idComprador;
}sProducts;

//PROTOTIPOS ABM
int sProducts_addProducts(sProducts array[], int TAM);
int sProducts_removeProducts(sProducts array[], int TAM);
int sProducts_modifyData(sProducts array[], int TAM);
void sProducts_initProducts(sProducts array[], int TAM);
int sProducts_printProducts(sProducts Pasajeros[], int TAM);
int sProducts_CargaForzada(sProducts listaPasajeros[]);
int sProducts_findProductsByID(sProducts array[], int TAM, int ID);
int sProducts_verifyUserProducts(sProducts productList[], int len, int userID) ;
int sProducts_BuyProduct(sProducts productos[], int TAM);
int sProducts_sortProducts(sProducts productos[], int TAM);
int sProducts_printUserProducts(sProducts Products[], int TAM, int idUsuario);
int sProducts_ReplaceStock(sProducts productos[], int TAM, int idUsuario);
int sProduct_sortProductsByStock(sProducts productos[], int TAM);
int sProducts_FindByName(sProducts productos[], int TAM_U, char nombreProducto[]);
int sProducts_printFindProductsByName(sProducts productos[], int TAM, char nombre[]);

#endif /* PRODUCTS_H_ */
