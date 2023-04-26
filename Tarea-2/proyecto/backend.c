#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashmap.h"
#include "arraylist.h"

#define MAXCHAR 30

//typedef char char[MAXCHAR];

typedef struct datosJugador
{
	char nombre[MAXCHAR];
	int habilidad;
	int cantItems;
	HashMap *item; // podria ser una lista u otra cosa igualmente

} datosJugador;

typedef struct item
{
	char nombre[MAXCHAR];
	int cantidad;
} item;

// Funciones etc

void mostrarLista(ArrayList *l) // imprime una lista de char, con valores espaciados.
{
	for (int i = 0; i < get_size(l); i++)
		printf("%s ", get(l, i));
}

void mostrarMapa(HashMap* mapa) // imprime un mapa de char, con valores espaciados.
{
	Pair *current = firstMap(mapa);
	while (current)
	{
		printf("%s\n", current->key);
		current = nextMap(mapa);
	}
}

void mostrarTodos(HashMap *jugadores) // imprime todos los jugadores.
{
	Pair *current = firstMap(jugadores);
	while (current)
		mostrarPerfil(jugadores, current->key);
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
datosJugador* crearJugador(){
	datosJugador *new = (datosJugador *)malloc(sizeof(datosJugador));
	if (!new)
		assert("No hay suficiente memoria");

	new->habilidad = 0;
	new->cantItems = 0;
	new->item = createHashMap(new->cantItems);
	return new;
}

item* crearItem(){
	item *new = (item *)malloc(sizeof(item));
	if (!new)
		assert("No hay suficiente memoria");

	new->cantidad = 0;
	return new;
}

void crearPerfil(HashMap *jugadores, char nombre[MAXCHAR])
{
	datosJugador *new = crearJugador();
	strcpy(new->nombre, nombre);
	insertMap(jugadores, nombre, new);
}

void mostrarPerfil(HashMap *jugadores, char nombre[MAXCHAR])
{
	Pair *aux = searchMap(jugadores, nombre);
	if (!aux)
	{
		printf("%s no existe..\n", nombre);
		return;
	}

	datosJugador *current = aux->value;
	if (!current)
	{
		printf("%s no existe..\n", nombre);
		return;
	}

	printf("Datos de %s:\n", nombre);
	printf("Nivel Habilidad : %d\n", current->habilidad);
	printf("Tamaño inventario : %d\n", current->cantItems);

	if (get_size(current->item) == 0)
	{
		printf("Inv vacio..\n");
		return;
	}

	printf("Contenido del inventario :");
	mostrarMapa(current->item);
}

void agregarItem(HashMap *jugadores, char nombre[MAXCHAR], char nombreItem[MAXCHAR])
{
	printf("\nnombre = %s\n", nombre);
	printf("\nnombreItem = %s\n", nombreItem);

	Pair *aux = searchMap(jugadores, nombre);
	if (!aux)
	{
		printf("%s no existe..\n", nombre);
		return;
	}

	datosJugador *current = aux->value;

	if (!current)
	{
		printf("%s no existe..\n", nombre);
		return;
	}
	// asumiendo que no se repite, sino hay que crear un sistema que evite repeticiones.
	printf("Agregando..\n");
	append(current->item, nombreItem);
}


void importarDesdeCSV(HashMap* jugadores, char archivo[MAXCHAR]) {
	FILE *csv = fopen(archivo, "r");

	if (!csv) {
    	printf("\nEl archivo no existe\n");
    	return;
  	}

  	char buffer[1000];
  	long linea = 0;
  	while (fgets(buffer, sizeof(buffer), csv)) {
    	linea++;
    	if (linea == 1) continue;
		printf("\n%d", linea);
    	buffer[strcspn(buffer, "\n")] = 0; // quitar el salto de linea

    	datosJugador *jugador = crearJugador();
    	int columna = 1;
    	char *valor = strtok(buffer, ",");

    	while (valor != NULL) {
			printf("-%d", columna);
    		if (columna == 1)
        		strcpy(jugador->nombre, valor);
    		if (columna == 2)
        		jugador->habilidad = (int)strtol(valor, NULL, 10);
      		if (columna == 3)
        		jugador->cantItems = (int)strtol(valor, NULL, 10);
      		if (columna > 3){
				item * item = crearItem();
				strcpy(item->nombre, valor);
				insertMap(jugador->item, item->nombre, item);
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

void exportarCSV(HashMap* jugadores, char archivo[MAXCHAR]) {
	FILE *csv = fopen(archivo, "w");

  	fprintf(csv, "Nombre,Habilidad,Cantidad de Items,Items\n");

  	Pair *current = firstMap(jugadores);
	while (current) {
		datosJugador *aux = current->value;
		fprintf(csv, "%s,%d,%d,", aux->nombre, aux->habilidad, aux->cantItems);
		Pair *currentItem = firstMap(aux->item);
		while (currentItem) {
			item *auxItem = currentItem->value;
			fprintf(csv, "%s,", auxItem->nombre);
			currentItem = nextMap(aux->item);
		}
		fprintf(csv, "\n");
		current = nextMap(jugadores);
	}

  	printf("\nArchivo exportado correctamente\n");
  	fclose(csv);
  	return;
}