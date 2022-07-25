#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

int controller_loadFromText(char* path, LinkedList* pArrayListPassenger);
int controller_loadFromBinary(char* path, LinkedList* pArrayListPassenger);
int controller_ListPeliculas(LinkedList* pArrayListPeliculas);
int controller_sortPeliculas(LinkedList* pArrayListPeliculas);
int controller_saveAsText(char* path, LinkedList* pArrayListPeliculas);
int controller_getUltimoId();

#endif /* SRC_CONTROLLER_H_ */
