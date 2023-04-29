#ifndef BACKEND_H
#define BACKEND_H

#include "HashMap/hashmap.h"
#define MAXCHAR 31



typedef char string[MAXCHAR]; 

typedef struct datosJugador datosJugador;
typedef struct accion accion;

HashMap* createHashMap(long); //recibe 0 para usar el default.

accion* crearAccion(int id, void* data);

void crearPerfil(HashMap* jugadores, string nombreJugador);

int agregarItem(HashMap* jugadores, string nombreJugador, string nombreItem);

void mostrarPerfil(HashMap* jugadores, string nombreJugador);
void mostrarTodos(HashMap* mapa);

void importarDesdeCSV(HashMap* jugadores, string archivo);
void exportarCsv(HashMap* jugadores, string archivo);
void mostrarTodosConUnItem(HashMap* jugadores, string nombreItem);





#endif