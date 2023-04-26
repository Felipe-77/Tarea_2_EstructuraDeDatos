#ifndef BACKEND_H
#define BACKEND_H
#include "hashmap.h"
#include "arraylist.h"
#define MAXCHAR 31



//typedef char char[MAXCHAR]; 

typedef struct datosJugador datosJugador;
typedef struct item item;

typedef char* nombresJugador;

HashMap* createHashMap(long); //recibe 0 para usar el default.

void crearPerfil(HashMap* jugadores,char nombre[MAXCHAR]);

void agregarItem(HashMap* jugadores, char nombre[MAXCHAR], char nombreItem[MAXCHAR]);

void mostrarPerfil(HashMap* jugadores,char nombre[MAXCHAR]);





#endif