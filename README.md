# Tarea 2 sistema de guardado

### Orden del codigo

Tenemos 4 archivos de extension C:
- La libreria de nuestro mapa.
- La libreria de una lista.
- Libreria con funciones para poder realizar la tarea asignada.
- Nuestro main, el cual se encarga de la interaccion con el usuario.

Luego podemos observar una carpeta csv:
Esta contiene 2 archivos csv para poder testear nuestro programa.

Además escribímos un script en bash para ejecutar el código más facilmente con el comando:
>sh execute.sh

Y un comando para actualizar el repositorio con el comnando:
>sh repo_update.sh {MESSAGE}


 

### Objetivo de la aplicación

Este proyecto creara un sistema para poder almacenar informacion de jugadores en un videojuego.
Este tomara el nombre de cada jugador, la cantidad de sus puntos de habilidades, cuantos items tiene en total, y cada item. 

En este caso:
- el nombre de cada jugador es un string de tamaño fijo.
- La cantidad de puntos de habilidad es un valor int.
- La cantidad de items seria un int igualmente.
- Finalmente tendremos que almacenar una lista de items.

Una vez tengamos nuestros datos almacenados, deseamos poder realizar
una serie de operaciones con esta informacion.

Tal como:

- Crear y Eliminar perfiles de jugadores
- Mostrar perfiles
	- Por cada uno
  - Mostrarlos todos
  - Mostrar solo jugadores que compartan un mismo item
- Agregar y elminar items a cada perfil
- Exportar e importar jugadores.
- Agregar puntos de habilidad a un jugador.
- Deshacer la última acción de un jugador.
---

### Diseño de la aplicación

Para poder almacenar la informacion, crearemos un mapa de jugadores.
Para acceder a cada jugador usaremos su nombre como clave, dentro almacenaremos:
- un nombre = char[30]
- un int para puntos de habilidad
- un int para cantidad de items
- una lista de un items.

Por otro lado, es necesario implementar un mapa de items para acceder a ellos facilmente y a la lista de jugadores que tienen ese item.

