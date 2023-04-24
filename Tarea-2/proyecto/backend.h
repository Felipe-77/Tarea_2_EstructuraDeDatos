#ifndef BACKEND_H
#define BACKEND_H
#include "hashmap.h"
#include "arraylist.h"
#define MAXCHAR 31


typedef char string[MAXCHAR]; 

typedef struct datosJugador datosJugador;
typedef string* nombresJugador;

HashMap* createHashMap(long); //recibe 0 para usar el default.

void crearPerfil(HashMap* jugadores,string nombre);

void agregarItem(HashMap* jugadores,HashMap* items, string nombre, string nombreItem);

void mostrarPerfil(HashMap* jugadores,string nombre);





#endif