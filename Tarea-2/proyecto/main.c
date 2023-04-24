#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include "backend.h"

#define SEPARADOR printf("\n***********************\n")

void menuOpcionesDeJugador(HashMap* jugadores){
	int opcion;
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
			string nombre;
			
			case 1:
				printf("\nIngrese el nombre para el nuevo perfil:\n");
				scanf("%30[^\n]s", nombre);
				getchar();
				SEPARADOR;
				
				crearPerfil(jugadores, nombre);
				break;
			case 2:
				
				printf("\nIngrese el nombre del perfil:\n");
				scanf("%30[^\n]s", nombre);
				getchar();
				SEPARADOR;
				mostrarPerfil(jugadores, nombre);
				break;
			case 3:
				printf("Funcionlaidad no implemetada por el momento\n");
				break;
			case 4:
				printf("Funcionlaidad no implemetada por el momento\n");
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

void menuAdministrarItems(HashMap* mapaJugadores, HashMap* mapaItems){
	int opcion;
	while (1){
		printf("Seleccione una de las siguientes opciones:\n\n");
		//opciones
		printf("1) Agregar item a jugador\n");
		printf("2) Eliminar item de jugador\n");
		printf("0) Volver al menu principal\n");

		scanf("%i", &opcion);
		getchar();
		switch (opcion){
			string nombreJugador, nombreItem;
			
			case 1:
				printf("\nIngrese el nombre del item:\n");
				scanf("%30[^\n]s", nombreItem);
				getchar();
				printf("\nIngrese el nombre del jugador:\n");
				scanf("%30[^\n]s", nombreJugador);
				getchar();
				SEPARADOR;
				
				agregarItem(mapaJugadores,mapaItems, nombreJugador, nombreItem);
				break;
			case 2:
				printf("Funcionlaidad no implemetada por el momento\n");
				
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
	HashMap* items = createHashMap(0);

	printf("\n¡Bienvenid@ al sitema de guardado de datos!\n\n");
	SEPARADOR;

	while (1){
		printf("\nMENU PRINCPAL\n");
		//opciones
		printf("1) Opciones de jugador/a\n");
		printf("2) Administrar items\n");
		printf("3) Importar/Exportar\n");
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
				menuAdministrarItems(jugadores,items);
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