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
	if (strcmp( (char*) str1, (char*) str2)) return 0;
	return 1;
}

Map* createMapStr()
{
	return createMap(igualStr);
	
}

void crearPerfil(Map* jugadores,string nombre)
{
	datosJugador* nuevoJugador = (datosJugador *)malloc(sizeof(datosJugador));
	strcpy(nuevoJugador->nombre,nombre);
	nuevoJugador->habilidad=0;
	nuevoJugador->cantItems=0;
	nuevoJugador->item = createList();

	printf("%s",nuevoJugador->nombre);
	
	insertMap(jugadores,nombre,nuevoJugador);
	
}

void agregarItem(Map* jugadores, string nombre, string item)
{
	if (firstMap(jugadores) == NULL){
		printf("No hay jugadores en el sistema\n");
		return;
	}
	datosJugador* jugador = searchMap(jugadores,nombre);
	
	if (jugador == NULL)
	{
		printf("El jugador no existe aun.\n");
		return;
	}

	jugador->cantItems++;
	append(jugador->item,nombre);
	
}

void mostrarPerfil(Map* jugadores,string nombre)
{
	/*
	datosJugador* jugador = firstMap(jugadores);
	if (igualStr(jugador->nombre,nombre)) printf("son iguales");
	if (!igualStr(jugador->nombre,nombre)) printf("no son iguales");
	*/
	
	if (firstMap(jugadores) == NULL){
		printf("No hay jugadores en el sistema\n");
		return;
	}
	datosJugador* jugador = searchMap(jugadores,nombre);
	if (jugador == NULL)
	{
		printf("%s",nombre);
		printf(" no existe..\n");
		return;
	}

	printf("%s: \nHabilidad %d\n Inv size %d Inv \ncontent: ",jugador->nombre,jugador->habilidad,jugador->cantItems);
	
	showAll(jugador->item);
	
	
}

void showMap(Map* map)
{
	printf("\nMostrando keys mapa\n");
	datosJugador* node = firstMap(map);
	if(node==NULL) return;
	for (node; nextMap(map)!=NULL; node=nextMap(map))
		printf("%s",node->nombre);
}