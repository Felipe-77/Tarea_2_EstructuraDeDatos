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
	int id;
	void * data;
};

// Funciones etc

void mostrarLista(ArrayList *l) // imprime una lista de char, con valores espaciados.
{
	for (int i = 0; i < get_size(l); i++)
		printf("%s ", get(l, i));
}

void mostrarItems(HashMap *mapa) // imprime todas las keys de un mapa.
{
	Pair * current = firstMap(mapa);
	while (current != NULL)
	{
		printf("\n- %s", current->key);
		current = nextMap(mapa);
	}
  printf("\n");
}

void mostrarTodos(HashMap* mapa) // imprime todas las keys de un mapa.
{
	Pair * current = firstMap(mapa);
	while (current != NULL)
	{
    printf("\n--------------------------------\n");
		mostrarPerfil(mapa, current->key);
		current = nextMap(mapa);
	}
  printf("\n--------------------------------\n");
}


//----------------------------------------------------------------
// Mapa de jugadores funciones.

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
	new->item = createHashMap(10);
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

void crearPerfil(HashMap *jugadores, string nombreJugador)
{
	Pair *aux = searchMap(jugadores, nombreJugador);
	if (aux)
	{
		printf("%s ya existe..\n", nombreJugador);
		return;
	}

	datosJugador *new = crearJugador();
	strcpy(new->nombre, nombreJugador);
	insertMap(jugadores, new->nombre, new);
	printf("\nJugador %s creado correctamente\n", nombreJugador);
	return;
}

void eliminarPerfil(HashMap *jugadores, string nombreJugador)
{
	eraseMap(jugadores, nombreJugador);
	printf("\nSe ha eliminado a %s\n", nombreJugador);
	return 1;
}

void mostrarPerfil(HashMap *jugadores, string nombreJugador)
{
	Pair *aux = searchMap(jugadores, nombreJugador);
	if (!aux)
	{
		printf("\n%s no existe..\n", nombreJugador);
		return;
	}

	datosJugador *current = aux->value;
	if (!current)
	{
		printf("\n%s no existe..\n", nombreJugador);
		return;
	}

	printf("\nDatos de %s\n", nombreJugador);
	printf("Puntos de habilidad: %d\n", current->habilidad);

	if (current->cantItems == 0)
	{
		printf("Inventario vacio..\n");
		return;
	}

	printf("Contenido del inventario:\n");
	if (current->cantItems > 1)
		printf("%d items\n", current->cantItems);
	else
		printf("%d item\n", current->cantItems);
	mostrarItems(current->item);
}

int agregarItem(HashMap *jugadores, string nombreJugador, string nombreItem)
{
	Pair *aux = searchMap(jugadores, nombreJugador);
	if (aux == NULL)
	{
		printf("\n%s no existe..\n", nombreJugador);
		return 0;
	}
	datosJugador *current = aux->value;

	Pair * item = searchMap(current->item, nombreItem);
	if (item != NULL){
		printf("\nEl item ya está en el inventario\n");
		return 0;
	}

	printf("\nAgregando item..\n");
	current->cantItems++;
	insertMap(current->item, nombreItem, nombreItem);
	printf("\nSe ha agregado el item..\n");

	return 1;
}

int eliminarItem(HashMap *jugadores, string nombreJugador, string nombreItem)
{
	Pair *aux = searchMap(jugadores, nombreJugador);
	if (aux == NULL)
	{
		printf("\n%s no existe..\n", nombreJugador);
		return 0;
	}
	datosJugador *current = aux->value;

	Pair *item = searchMap(current->item, nombreItem);
	if (item == NULL)
	{
		printf("\n%s no existe..\n", nombreItem);
		return 0;
	}

	printf("\nEliminando item..\n");
	current->cantItems--;
	eraseMap(current->item, nombreItem);
	printf("\nSe eliminado el item..\n");

	return 1;
}

int agregarPuntosHabilidad(HashMap* jugadores, string nombreJugador, int puntosNuevos)
{
	Pair * current = searchMap(jugadores, nombreJugador);
	if (current == NULL)
	{
		printf("\n%s no existe..\n", nombreJugador);
		return 0;
	}
	datosJugador * jugador = current->value;
	jugador->habilidad += puntosNuevos;
	printf("\nSe han agregado %d puntos de habilidad a %s\n", puntosNuevos, nombreJugador);


	return 1;

}

void importarDesdeCSV(HashMap* jugadores, string archivo) 
{
	free(jugadores);
	jugadores = createHashMap(0);
	FILE *csv = fopen(archivo, "r");
	clean(jugadores);
	jugadores = createHashMap(1000);
	if (!csv) {
    	printf("\nEl archivo no existe\n");
    	return;
  	}

  	char buffer[1000];
  	long linea = 0;
  	while (fgets(buffer, sizeof(buffer), csv)) {
    	linea++;
    	if (linea == 1) continue;
    	buffer[strcspn(buffer, "\n")] = 0; // quitar el salto de linea

    	datosJugador *jugador = crearJugador();
    	int columna = 1;
    	char *valor = strtok(buffer, ",");

    	while (valor != NULL) {
    		if (columna == 1)
        		strcpy(jugador->nombre, valor);
    		if (columna == 2)
        		jugador->habilidad = (int)strtol(valor, NULL, 10); 
      		if (columna == 3)
        		jugador->cantItems = (int)strtol(valor, NULL, 10);
      		if (columna > 3){
				string * item = (string *)malloc(sizeof(char) * MAXCHAR);
				strcpy(item, valor);
				insertMap(jugador->item, item, item);
	  		}
			valor = strtok(NULL, ",");
    		columna++;
    	}
    	insertMap(jugadores, jugador->nombre, jugador);
		printf("\ninsercion de linea %d\n", linea);
  	}

  	printf("\nArchivo importado correctamente\n");
  	fclose(csv);
  	return;
}

/*void exportarCsv(HashMap* jugadores) {

	string archivo;
	printf("\nIngrese el nombre para el nuevo archivo:\n");
	scanf("%30[^\n]s", archivo);
	getchar();

  	FILE *nuevoCsv = fopen(archivo, "r");
  
  	if (nuevoCsv) {
    	printf("\nEl archivo ya existe\n");
    	fclose(nuevoCsv);
    	return;
  	}
  
  	nuevoCsv = fopen(archivo, "w");

  	if (!nuevoCsv) {
    	printf("No se puede crear el archivo\n");
    	fclose(nuevoCsv);
    	return;
  	}
	
  	Pair * current = (Pair *)firstMap(jugadores);
  	while (current != NULL) {
		datosJugador * jugador = current->value;
    	fprintf(nuevoCsv, "%s,%d,%d", jugador->nombre, jugador->habilidad, jugador->cantItems);

    	for (int k = 0; k < jugador->cantItems; k++) {

    		fprintf(nuevoCsv,",%s", jugador->item->key);
    	}
    	fprintf(nuevoCsv, "\n");
  	}

  	printf("\nArchivo exportado correctamente\n");
  	fclose(nuevoCsv);
  	return;
}
*/

void deshacerUltAccion(HashMap* jugadores, string nombreJugador)
{
	Pair * current = (Pair *)searchMap(jugadores, nombreJugador);
	if (current == NULL)
	{
		printf("\n%s no existe..\n", nombreJugador);
		return;
	}

	datosJugador* jugador = (datosJugador *)current->value;
	ArrayList * l = jugador->pilaAcciones;
	if (get_size(l) == 0)
	{
		printf("\nNo hay acciones para deshacer..\n");
		return;
	}

	int top = (get_size(l) - 1);
	accion * ultAccion =  get(l, top);
	
	int id = ultAccion->id;
	if (id == id_agregarHabilidad)
	{
		jugador->habilidad -= (int)ultAccion->data;
		printf("\nSe han eliminado %d puntos de habilidad a %s\n", ultAccion->data, jugador->nombre);
	}

	if (id == id_agregarItem)
	{
		eraseMap(jugador->item, ultAccion->data);
		printf("\nSe eliminado el ultimo item\n");
	}

	if (id == id_eliminarItem)
	{
		insertMap(jugador->item, ultAccion->data, ultAccion->data);
		printf("\nSe ha recuperado el ultimo item\n");
	}

	pop(l, top);
}
