#ifndef BACKEND_H
#define BACKEND_H
#include "HashMap/hashmap.h"
#include "arraylist/arraylist.h"
#define MAXCHAR 31



typedef char string[MAXCHAR]; 

typedef struct datosJugador datosJugador;

typedef char* nombresJugador;

HashMap* createHashMap(long); //recibe 0 para usar el default.

void crearPerfil(HashMap* jugadores);

void agregarItem(HashMap* jugadores);

void mostrarPerfil(HashMap* jugadores);

void exportarCsv(HashMap* jugadores);





#endif