#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#define MAXCHAR 30


typedef char string[MAXCHAR]; 

typedef struct jugadores {
	char nombre[MAXCHAR];
	int habilidad;
	int cantItems;
	string* item; //podria ser una lista u otra cosa igualmente

} jugadores;

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

Map* createMapStr();
{
	Map* new = createMap(igualStr);
}

crearPerfil(Map* jugadores,string nombre)
{
	if (jugadores == NULL) return NULL;
	
	
	
}