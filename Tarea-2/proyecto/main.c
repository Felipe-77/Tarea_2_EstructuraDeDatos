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
			case 1:
				crearPerfil(jugadores);
				SEPARADOR;
				break;
			case 2:
				mostrarPerfil(jugadores);
				SEPARADOR;
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

void menuAdministrarItems(HashMap* mapaJugadores){
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
			
			
			case 1:
				agregarItem(mapaJugadores);
				SEPARADOR;
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

void menuImportarExportar(HashMap* jugadores){
	int opcion;
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
				importarDesdeCSV(jugadores);
				SEPARADOR;
				break;
			case 2:
				exportarCsv(jugadores);
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
				mostrarKeys(jugadores);
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