#ifndef BACKEND_H
#define BACKEND_H

#include "HashMap/hashmap.h"
#define MAXCHAR 31



typedef char string[MAXCHAR]; 

typedef struct datosJugador datosJugador;
typedef struct accion accion;

HashMap* createHashMap(long); //recibe 0 para usar el default.
datosJugador* crearJugador(void);
accion* crearAccion(int id, void* data);

void crearPerfil(HashMap* jugadores, string nombreJugador);
void eliminarPerfil(HashMap *jugadores, string nombreJugador);

void mostrarPerfil(HashMap* jugadores, string nombreJugador);
void mostrarTodos(HashMap* mapa);
void mostrarItems(HashMap *mapa);
void mostrarTodosConUnItem(HashMap* jugadores, string nombreItem);

int agregarItem(HashMap *jugadores, string nombreJugador, string nombreItem);
int eliminarItem(HashMap *jugadores, string nombreJugador, string nombreItem);

int agregarPuntosHabilidad(HashMap* jugadores, string nombreJugador, int puntosNuevos);

void importarDesdeCSV(HashMap* jugadores, string archivo);
void exportarCsv(HashMap* jugadores, string archivo);

void deshacerUltAccion(HashMap* jugadores, string nombreJugador);

#endif