#ifndef BACKEND_H
#define BACKEND_H
#include "Map.h"
#include "arraylist.h"
#define MAXCHAR 31


typedef char string[MAXCHAR]; 

typedef struct datosJugador datosJugador;
typedef string* nombresJugador;

int igualStr(void* str1,void*str2);

Map* createMapStr();

void crearPerfil(Map* jugadores,string nombre);

void agregarItem(Map* jugadores, string nombre, string item);

void mostrarPerfil(Map* jugadores,string nombre);




#endif