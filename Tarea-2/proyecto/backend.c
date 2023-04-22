#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#define MAXCHAR 30


typedef char string[MAXCHAR]; 

typedef struct datosJugador {
	char nombre[MAXCHAR];
	int habilidad;
	int cantItems;
	string* item; //podria ser una lista u otra cosa igualmente

} datosJugador;

typedef string* nombresJugador; //Hecho para crear listas
							   //de nombre jugador

//FUNCION HASH
//sirve para ambos mapas.

int hash(string key);

//----------------------------------------------------------------
//Mapa de jugadores funciones.

int igualStr(void* str1,void*str2)
{
	if (strcmp( (char*) str1, (char*) str2)) return 1;
	return 0;
}

Map* createMapStr()
{
	return createMap(igualStr);
	
}

void crearPerfil(Map* jugadores,string nombre)
{
	datosJugador* nuevoJugador = malloc(sizeof(datosJugador));
	nuevoJugador->habilidad=0;
	nuevoJugador->cantItems=0;
	nuevoJugador->item = NULL;	
	
	insertMap(jugadores,nombre,nuevoJugador);
	
}