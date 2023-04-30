#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "HashMap/hashmap.h"
#include "ArrayList/arraylist.h"

#define MAXCHAR 31

#define id_agregarHabilidad 1
#define id_agregarItem 2
#define id_eliminarItem 3


typedef char string[MAXCHAR];
typedef struct datosJugador datosJugador;
typedef struct accion accion;

struct datosJugador
{
	string nombre;
	int habilidad;
	int cantItems;
	HashMap *item; // podria ser una lista u otra cosa igualmente
	ArrayList *pilaAcciones;
};

struct accion 
{
	int id;		//Guarda el id de la accion (agregarHabilidad, agregarItem, eliminarItem)
	void * data;	//Guarda el dato de la accion (nombreItem o puntosHabilidad)
};

//------------------------------------------------------------------------------
// Funciones para mostrar cosas.

void mostrarLista(ArrayList *l) // imprime una lista de char, con valores espaciados.
{
	for (int i = 0; i < get_size(l); i++)
		printf("%s ", get(l, i));
}

void mostrarItems(HashMap *mapa) // Muestra las keya del mapa item
{
	Pair * current = (Pair *)firstMap(mapa);
	while (current != NULL)
	{
		printf("\n- %s", current->key);
		current = (Pair *)nextMap(mapa);
	}
  	printf("\n");
}

void mostrarTodos(HashMap* mapa) // Muestra los perfiles de todos los jugadores
{
	Pair * current = (Pair *)firstMap(mapa);
	while (current != NULL)
	{
    	printf("\n--------------------------------\n");
		mostrarPerfil(mapa, current->key);
		current = (Pair *)nextMap(mapa);
	}
  	printf("\n--------------------------------\n");
}


// funciones para crear mapa y los structs.

HashMap *createHashMap(long capacity)
{
	HashMap *new = NULL;
	if (capacity == 0)
		new = createMap(100);
	else
		new = createMap(capacity);

	if (!new)
		assert("No hay suficiente memoria");

	return new;
}

datosJugador* crearJugador()
{
	datosJugador *new = (datosJugador *)malloc(sizeof(datosJugador));
	if (!new)
		assert("No hay suficiente memoria");

	new->habilidad = 0;
	new->cantItems = 0;
	new->item = createHashMap(50);
	new->pilaAcciones = createList();
	return new;
}

accion* crearAccion(int id, void* data)
{
	accion *new = (accion *)malloc(sizeof(accion));
	if (!new) assert("No hay suficiente memoria");
	new->id = id;
	new->data = data;

	return new;
}

//Funciones para el menu

void crearPerfil(HashMap *jugadores, string nombreJugador)
{
	Pair *aux = (Pair *)searchMap(jugadores, nombreJugador); //busca si el jugador ya existe
	if (aux)
	{
		printf("\nEl jugador %s ya existe..\n", nombreJugador);
		return;
	}

	datosJugador *new = crearJugador();	//crea el jugador
	strcpy(new->nombre, nombreJugador);
	insertMap(jugadores, new->nombre, new);
	printf("\nJugador '%s' creado correctamente\n", nombreJugador);
	return;
}

void eliminarPerfil(HashMap *jugadores, string nombreJugador)	//elimina un jugador
{
	eraseMap(jugadores, nombreJugador);
	printf("\nSe ha eliminado a %s\n", nombreJugador);
	return 1;
}

void mostrarPerfil(HashMap *jugadores, string nombreJugador)	//muestra el perfil de un jugador
{
	Pair *aux = (Pair *)searchMap(jugadores, nombreJugador);
	if (!aux)
	{
		printf("\nEl jugador %s no existe..\n", nombreJugador);
		return;
	}

	datosJugador *current = aux->value;
	if (!current)
	{
		printf("\nEl jugador %s no existe..\n", nombreJugador);
		return;
	}

	printf("\nDatos de %s\n", nombreJugador);
	printf("Puntos de habilidad: %d\n", current->habilidad);

	if (current->cantItems == 0)	//si no tiene items se muestra un mensaje
	{
		printf("Inventario vacío..\n");
		return;
	}

	printf("Contenido del inventario:\n");
	if (current->cantItems > 1)
		printf("%d items\n", current->cantItems);
	else
		printf("%d item\n", current->cantItems);
	mostrarItems(current->item);	//se muestran los items del jugador
}

int agregarItem(HashMap *jugadores, string nombreJugador, string nombreItem)	//agrega un item al inventario del jugador
{
	Pair *aux = (Pair *)searchMap(jugadores, nombreJugador);	//busca si el jugador existe
	if (aux == NULL)
	{
		printf("\nEl jugador %s no existe..\n", nombreJugador);
		return 0;
	}
	datosJugador *current = aux->value;

	Pair * item = (Pair *)searchMap(current->item, nombreItem);	//busca si el item ya está en el inventario
	if (item != NULL){
		printf("\nEl item ya está en el inventario\n");
		return 0;
	}

	printf("\nAgregando item..\n");
	current->cantItems++;
	insertMap(current->item, nombreItem, nombreItem);	//agrega el item al mapa de items del jugador
	printf("\nSe ha agregado el item..\n");

	return 1;
}

int eliminarItem(HashMap *jugadores, string nombreJugador, string nombreItem)	//elimina un item del inventario del jugador
{
	Pair *aux = (Pair *)searchMap(jugadores, nombreJugador);	//busca si el jugador existe
	if (aux == NULL)
	{
		printf("\nEl jugador %s no existe..\n", nombreJugador);
		return 0;
	}
	datosJugador *current = aux->value;

	Pair *item = (Pair *)searchMap(current->item, nombreItem);	//busca si el item está en el inventario
	if (item == NULL)
	{
		printf("\n%s no posee el item %s..\n", nombreJugador, nombreItem);
		return 0;
	}

	printf("\nEliminando item..\n");
	current->cantItems--;
	eraseMap(current->item, nombreItem);	//elimina el item del mapa de items del jugador
	printf("\nSe ha eliminado el item..\n");

	return 1;
}

int agregarPuntosHabilidad(HashMap* jugadores, string nombreJugador, int puntosNuevos)	//agrega puntos de habilidad al jugador
{
	Pair * current = (Pair *)searchMap(jugadores, nombreJugador);	//busca si el jugador existe
	if (current == NULL)
	{
		printf("\nEl jugador %s no existe..\n", nombreJugador);
		return 0;
	}
	datosJugador * jugador = current->value;
	jugador->habilidad += puntosNuevos;	//se suman los puntos de habilidad al jugador
	printf("\nSe han agregado %d puntos de habilidad a %s\n", puntosNuevos, nombreJugador);

	return 1;
}

void importarDesdeCSV(HashMap* jugadores, string archivo) 
{
	free(jugadores);	//se libera la memoria del mapa de jugadores
	jugadores = createHashMap(0);	//se crea un nuevo mapa de jugadores
	FILE *csv = fopen(archivo, "r");	//se abre el archivo csv
	if (!csv) {
    	printf("\nEl archivo no existe\n");
    	return;
  	}

  	char buffer[1000];
  	long linea = 0;
  	while (fgets(buffer, sizeof(buffer), csv)) {	//se lee el archivo linea por linea
    	linea++;
    	if (linea == 1) continue;	//se salta la primera linea
    	buffer[strcspn(buffer, "\n") - 1] = 0; // quitar el salto de linea de la linea leida

    	datosJugador *jugador = crearJugador();	//se crea un nuevo jugador
    	int columna = 1;
    	char *valor = strtok(buffer, ",");	//se separa en palabras la linea por comas

    	while (valor != NULL) {
    		if (columna == 1){	//se guarda el nombre del jugador
        		strcpy(jugador->nombre, valor);
				puts(jugador->nombre);
			}
    		if (columna == 2)	//se guarda la habilidad del jugador
        		jugador->habilidad = (int)strtol(valor, NULL, 10); 	
      		if (columna == 3)
        		jugador->cantItems = (int)strtol(valor, NULL, 10);	//se guarda la cantidad de items del jugador
      		if (columna > 3){
				string * item = (string *)malloc(sizeof(char) * MAXCHAR);	//se crea un nuevo item
				strcpy(item, valor);
				insertMap(jugador->item, item, item);	//se agrega el item al mapa de items del jugador
	  		}
			valor = strtok(NULL, ",");
    		columna++;
    	}
    	insertMap(jugadores, jugador->nombre, jugador);	//se agrega el jugador al mapa de jugadores
		printf("\nInserción de linea %d\n", linea);
  	}

    system("clear");
  	printf("\nArchivo importado correctamente\n");
  	fclose(csv);
  	return;
}

void exportarCsv(HashMap* jugadores, string archivo) {
  	FILE *nuevoCsv = fopen(archivo, "r");	//se comprueba si existe el archivo
  
  	if (nuevoCsv) {	
    	printf("\nEl archivo ya existe\n");
    	fclose(nuevoCsv);
    	return;
  	}

  	nuevoCsv = fopen(archivo, "w");	//se crea el archivo csv

  	if (!nuevoCsv) {
		printf("No se puede crear el archivo\n");
    	fclose(nuevoCsv);
    	return;
  	}
	
  	Pair * current = (Pair *)firstMap(jugadores);	//se recorre el mapa de jugadores
  	while (current != NULL) {
	  	datosJugador * jugador = current->value;	//se obtiene el jugador
    	fprintf(nuevoCsv, "%s,%d,%d", jugador->nombre, jugador->habilidad, jugador->cantItems);

    	Pair * item = (Pair *)firstMap(jugador->item);	//se recorre el mapa de items del jugador
	  	while(item != NULL){
		  	fprintf(nuevoCsv, ",%s", item->key);	//se escribe el item en el archivo csv
		  	item = (Pair *)nextMap(jugador->item);
	  	}
	  	fprintf(nuevoCsv, "\n");
	  	current = (Pair *)nextMap(jugadores);	//se obtiene el siguiente jugador
  	}
	fclose(nuevoCsv);	//se cierra el archivo csv

 	system("clear");
  	printf("\nArchivo exportado correctamente\n");
  	
  	return;
}


void deshacerUltAccion(HashMap* jugadores, string nombreJugador)
{
	Pair * current = (Pair *)searchMap(jugadores, nombreJugador);	//busca si el jugador existe
	if (current == NULL)
	{
		printf("\nEl jugador %s no existe..\n", nombreJugador);
		return;
	}

	datosJugador* jugador = (datosJugador *)current->value;	//se obtiene el jugador
	ArrayList * l = jugador->pilaAcciones;	//se obtiene la pila de acciones del jugador
	if (get_size(l) == 0)	//se comprueba si hay acciones para deshacer
	{
		printf("\nNo hay acciones para deshacer..\n");
		return;
	}

	int top = (get_size(l) - 1);	//se obtiene el top de la pila
	accion * ultAccion =  get(l, top);	//se obtiene la última acción
	
	int id = ultAccion->id;	//se obtiene el id de la última acción
	if (id == id_agregarHabilidad)
	{
		jugador->habilidad -= (int)ultAccion->data;
		printf("\nSe han eliminado %d puntos de habilidad a %s\n", ultAccion->data, jugador->nombre);
	}

	if (id == id_agregarItem)	//se comprueba si se agregó un item
	{
		eraseMap(jugador->item, ultAccion->data);	//se elimina el item del mapa de items del jugador
		jugador->cantItems--;
		printf("\nSe ha eliminado el último item\n");
	}

	if (id == id_eliminarItem)	//se comprueba si se eliminó un item
	{
		insertMap(jugador->item, ultAccion->data, ultAccion->data);	//se agrega el item al mapa de items del jugador
		jugador->cantItems++;
		printf("\nSe ha recuperado el último item\n");
	}

	pop(l, top);
}

void mostrarTodosConUnItem(HashMap* jugadores, string nombreItem)	//muestra todos los jugadores que tienen un item
{
	int cont = 0;
	Pair * current = (Pair *)firstMap(jugadores);	//se recorre el mapa de jugadores
	while (current != NULL) {
		datosJugador * jugador = current->value;	//se obtiene el jugador
		Pair * item = (Pair *)searchMap(jugador->item, nombreItem);	//se busca el item en el mapa de items del jugador
		if (item != NULL)	//se comprueba si el jugador tiene el item
		{
			printf("\n- %s\n", jugador->nombre);	
			cont++;
		}
		current = (Pair *)nextMap(jugadores);
	}
	if (cont == 0)
		printf("\nNo hay jugadores con el item %s\n", nombreItem);
}
