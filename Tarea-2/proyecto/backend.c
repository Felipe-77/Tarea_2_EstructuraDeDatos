#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashmap.h"
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




// Funciones etc

void mostrarLista(ArrayList* l) //imprime una lista de string, con valores espaciados.
{
	for (int i = 0; i < get_size(l) ; i++)
		printf("%s ",get(l,i));
}

//----------------------------------------------------------------
//Mapa de jugadores funciones.

HashMap* createHashMap(long capacity)
{
	HashMap* new=NULL;
	if (capacity==0)
		new = createMap(100);
	else 
		new = createMap(capacity);
	
	if (!new) assert("No hay suficiente memoria");

	return new;
}

void crearPerfil(HashMap* jugadores,string nombre)
{
	datosJugador* new = malloc(sizeof(datosJugador));
	if (!new) assert("No hay suficiente memoria");

	strcpy(new->nombre,nombre);

	new->habilidad=0;
	new->cantItems=0;
	new->item=createList();
	
	insertMap(jugadores,nombre,new);
}

void mostrarPerfil(HashMap* jugadores,string nombre)
{
	Pair* aux = searchMap(jugadores,nombre);
	if (!aux)
	{
		printf("%s no existe..\n",nombre);
		return;
	}

	datosJugador* current = aux->value;
	if (!current) 
	{
		printf("%s no existe..\n",nombre);
		return;
	}

	printf("Datos de %s:\n",nombre);
	printf("Nivel Habilidad : %d\n",current->habilidad);
	printf("Tamaño inventario : %d\n",current->cantItems);

	if (get_size(current->item) == 0)
	{
		printf("Inv vacio..\n");
		return;
	}

	printf("Contenido del inventario : [ ");
	mostrarLista(current->item);
	printf("]\n");
		

}

void agregarItem(HashMap* jugadores,HashMap* items, string nombre, string nombreItem)
{
	Pair* aux = searchMap(jugadores,nombre);
	if (!aux)
	{
		printf("%s no existe..\n",nombre);
		return;
	}

	datosJugador* current = aux->value;
	if (!current) 
	{
		printf("%s no existe..\n",nombre);
		return;
	}
	//asumiendo que no se repite, sino hay que crear un sistema que evite repeticiones.
	printf("Agregando..\n");
	append(current->item,nombreItem);


}



