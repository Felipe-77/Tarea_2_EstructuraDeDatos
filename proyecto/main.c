#include <stdio.h>
#include <stdlib.h>
#include "HashMap/hashmap.h"
#include "ArrayList/arraylist.h"
#include "backend.h"

#define SEPARADOR printf("\n***********************\n")
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


void menuOpcionesDeJugador(HashMap* jugadores){
	int opcion;
	int puntosHabilidad;
	string nombreJugador;

	while (1){
		printf("Seleccione una de las siguientes opciones:\n\n");
		//opciones
		printf("1) Crear perfil\n");
		printf("2) Mostrar perfil\n");
		printf("3) Agregar puntos de habilidad\n");
		printf("4) Deshacer última acción\n");
		printf("0) Volver al menu principal\n");

		scanf("%i", &opcion);
		getchar();
		switch (opcion){
			case 1:
				printf("\nIngrese nombre del jugador:\n");
				scanf("%30[^\n]s", nombreJugador);
				getchar();

				crearPerfil(jugadores, nombreJugador);
				SEPARADOR;
				break;
			case 2:
				printf("\nIngrese nombre del jugador:\n");
				scanf("%30[^\n]s", nombreJugador);
				getchar();

				mostrarPerfil(jugadores, nombreJugador);
				SEPARADOR;
				break;
			case 3:
				printf("\nIngrese nombre del jugador:\n");
				scanf("%30[^\n]s", nombreJugador);
				getchar();

				printf("\n¿Cuántos puntos de habilidad desea agregar?:\n");
				scanf("%i", &puntosHabilidad);
				getchar();

				if (agregarPuntosHabilidad(jugadores, nombreJugador, puntosHabilidad) == 1){
					accion * accion = crearAccion(id_agregarHabilidad, puntosHabilidad);
					Pair * current = (Pair *) searchMap(jugadores, nombreJugador);
					datosJugador* jugador = (datosJugador *) current->value;
					append(jugador->pilaAcciones, accion);	// se agrega a la pila de acciones.
				}
				SEPARADOR;
				break;
			case 4:
				printf("\nIngrese nombre del jugador:\n");
				scanf("%30[^\n]s", nombreJugador);
				getchar();

				deshacerUltAccion(jugadores, nombreJugador);
				SEPARADOR;
				break;
			case 0:
				printf("Volviendo...\n");
				return;
			default:
				printf("Opción inválida\n\n");
				break;
		}
	}
}

void menuAdministrarItems(HashMap* jugadores){
	int opcion;
	string nombreJugador;

	while (1){
		printf("Seleccione una de las siguientes opciones:\n\n");
		//opciones
		printf("1) Agregar item a jugador\n");
		printf("2) Eliminar item de jugador\n");
		printf("0) Volver al menu principal\n");

		scanf("%i", &opcion);
		getchar();
		switch (opcion){
			
			
			case 1:
				printf("\nIngrese nombre del jugador:\n");
				scanf("%30[^\n]s", nombreJugador);
				getchar();

				string* nombreItem = malloc(sizeof(char) * MAXCHAR);
				printf("\nIngrese nombre del item:\n");
				scanf("%30[^\n]s", nombreItem);
				getchar();

				if (agregarItem(jugadores, nombreJugador, nombreItem) == 1){
					accion * accion = crearAccion(id_agregarItem, nombreItem);
					Pair * current = (Pair *) searchMap(jugadores, nombreJugador);
					datosJugador* jugador = (datosJugador *) current->value;
					append(jugador->pilaAcciones, accion);	// se agrega a la pila de acciones.				
				}
				SEPARADOR;
				break;
			case 2:
				printf("\nIngrese nombre del jugador:\n");
				scanf("%30[^\n]s", nombreJugador);
				getchar();

				printf("\nIngrese nombre del item:\n");
				scanf("%30[^\n]s", nombreItem);
				getchar();

				if (eliminarItem(jugadores, nombreJugador, nombreItem) == 1){
					string* itemRecuperado = malloc(sizeof(char) * MAXCHAR);
					strcpy(itemRecuperado, nombreItem);

					accion * accion = crearAccion(id_eliminarItem, itemRecuperado);
					Pair * current = (Pair *) searchMap(jugadores, nombreJugador);
					datosJugador* jugador = (datosJugador *) current->value;
					append(jugador->pilaAcciones, accion);	// se agrega a la pila de acciones.
				}
				SEPARADOR;
				break;
			case 0:
				printf("Volviendo...\n");
				return;
			default:
				printf("Opción inválida\n\n");
				break;
		}
	}
}

void menuImportarExportar(HashMap* jugadores){
	int opcion;
	string archivo;
	while (1){
		printf("Seleccione una de las siguientes opciones:\n\n");
		//opciones
		printf("1) Importar datos\n");
		printf("2) Exportar datos\n");
		printf("0) Volver al menu principal\n");

		scanf("%i", &opcion);
		getchar();
		switch (opcion){
			case 1:
				printf("\nIngrese nombre del archivo:\n");
				scanf("%30[^\n]s", archivo);
				getchar();

				importarDesdeCSV(jugadores, archivo);
				SEPARADOR;
				break;
			case 2:
				//exportarCsv(jugadores);
				SEPARADOR;
				break;
			case 0:
				printf("Volviendo...\n");
				return;
			default:
				printf("Opción inválida\n\n");
				break;
		}
	}
}


int main()
{
	int opcion;
	HashMap* jugadores = createHashMap(0);

	printf("\n¡Bienvenid@ al sitema de guardado de datos!\n\n");
	SEPARADOR;

	while (1){
		printf("\nMENU PRINCPAL\n");
		//opciones
		printf("1) Opciones de jugador/a\n");
		printf("2) Administrar items\n");
		printf("3) Importar/Exportar\n");
		printf("4) Mostrar todos los jugadores\n");
		printf("0) Salir\n");
		scanf("%i", &opcion);
		getchar();

		SEPARADOR;
		switch (opcion){
			case 1:
				menuOpcionesDeJugador(jugadores);
				SEPARADOR;
				break;
			case 2:
				menuAdministrarItems(jugadores);
				SEPARADOR;
				break;
			case 3:
				menuImportarExportar(jugadores);
				SEPARADOR;
				break;
			case 4:
				mostrarTodos(jugadores);
				SEPARADOR;
				break;
			case 0:
				printf("Saliendo...\n");
				return 0;
			default:
				printf("Opción inválida\n\n");
				break;
		}
	}
	return EXIT_SUCCESS;
}