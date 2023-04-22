#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "arraylist.h"

#define MAXCHAR 30



typedef char string[MAXCHAR]; 

typedef struct datosJugador {
	string nombre;
	int habilidad;
	int cantItems;
	ArrayList* item; //podria ser una lista u otra cosa igualmente

} datosJugador;

typedef string* nombresJugador; //Hecho para crear listas
							   //de nombre jugador



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
	strcpy(nuevoJugador->nombre,nombre);
	nuevoJugador->habilidad=0;
	nuevoJugador->cantItems=0;
	nuevoJugador->item = createList();
	
	insertMap(jugadores,nombre,nuevoJugador);
	
}

void agregarItem(Map* jugadores, string nombre, string item)
{
	
	datosJugador* jugador = searchMap(jugadores,nombre);
	
	if (jugador == NULL)
	{
		printf("El jugador no existe aun.\n");
		return;
	}

	jugador->cantItems++;
	append(jugador->item,nombre);
	
}

void mostrarPerfil(Map* jugadores, string nombre)
{
	
	datosJugador* jugador = searchMap(jugadores,nombre);

	printf("%s: \nHabilidad %d\n Inv size %d Inv \ncontent: ",jugador->nombre,jugador->habilidad,jugador->cantItems);
	showAll(jugador->item);
	
}