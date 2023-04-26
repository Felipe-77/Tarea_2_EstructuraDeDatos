#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashmap.h"
#include "arraylist.h"

#define MAXCHAR 30

typedef char string[MAXCHAR];

typedef struct datosJugador
{
	string nombre;
	int habilidad;
	int cantItems;
	HashMap *item; // podria ser una lista u otra cosa igualmente

} datosJugador;

// Funciones etc

void mostrarLista(ArrayList *l) // imprime una lista de char, con valores espaciados.
{
	for (int i = 0; i < get_size(l); i++)
		printf("%s ", get(l, i));
}

void mostrarKeys(HashMap* mapa) // imprime todas las keys de un mapa.
{
	Pair * current = firstMap(mapa);
	while (current != NULL)
	{
		printf("%s\n", current->key);
		current = nextMap(mapa);
	}
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
	new->item = createHashMap(10);
	return new;
}


void crearPerfil(HashMap *jugadores)
{
	string nombreJugador;
	printf("\nIngrese nombre del jugador:\n");
	scanf("%30[^\n]s", nombreJugador);
	getchar();

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
}

void mostrarPerfil(HashMap *jugadores)
{
	string nombreJugador;
	printf("\nIngrese nombre del jugador:\n");
	scanf("%30[^\n]s", nombreJugador);
	getchar();

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

	printf("\n");
	printf("Datos de %s:\n", nombreJugador);
	printf("Nivel Habilidad : %d\n", current->habilidad);
	printf("Tamaño inventario : %d\n", current->cantItems);

	if (current->cantItems == 0)
	{
		printf("Inv vacio..\n");
		return;
	}

	printf("Contenido del inventario :\n");
	printf("(*)%d items : \n", current->cantItems);
	mostrarKeys(current->item);
}

void agregarItem(HashMap *jugadores)
{
	string nombreJugador;
	printf("\nIngrese nombre del jugador:\n");
	scanf("%30[^\n]s", nombreJugador);
	getchar();

	Pair *aux = searchMap(jugadores, nombreJugador);
	if (aux == NULL)
	{
		printf("%s no existe..\n", nombreJugador);
		return;
	}
	datosJugador *current = aux->value;

	string * nombreItem = malloc(sizeof(char) * MAXCHAR);
	printf("\nIngrese nombre del item:\n");
	scanf("%30[^\n]s", nombreItem);
	getchar();

	// asumiendo que no se repite, sino hay que crear un sistema que evite repeticiones.
	printf("\nAgregando item..\n");
	current->cantItems++;
	insertMap(current->item, nombreItem, nombreItem);
}


void importarDesdeCSV(HashMap* jugadores) {
	string archivo;
	printf("\nIngrese nombre del archivo:\n");
	scanf("%30[^\n]s", archivo);
	getchar();

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

    		fprintf(nuevoCsv,",%s", jugador->item[k]->key);
    	}
    	fprintf(nuevoCsv, "\n");
  	}

  	printf("\nArchivo exportado correctamente\n");
  	fclose(nuevoCsv);
  	return;
}
*/
