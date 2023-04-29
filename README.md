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
### Diseño de la aplicación

Para poder almacenar la informacion, crearemos un mapa de jugadores.
Para acceder a cada jugador usaremos su nombre como clave, dentro almacenaremos:
- un nombre = char[30]
- un int para puntos de habilidad
- un int para cantidad de items
- un mapa de un items.

La decision de guardar un puntero a un mapa es porque, nos da los siguientes beneficios importantes. Estos correspondientes a ciertas operaciones que es util si un jugador tiene muchos items.

La busqueda de un mapa siempre sera una complejidad O(1), esto nos ayuda mucho, para poder buscar los items.
Lo que es conveniente si deseamos poder analizar si un jugador posee algun item. Y en el caso de la eliminacion es mejor que su alternativa, la lista, que para datos que podrian hallarse en la mitad seria mas lento.

Podriamos decir entonces que, si quisiesemos recorrer jugadores solo con un item, revisando que cada jugador tenga el item que buscamos. Para una lista seria, O(n*n) = O(n²) al hacer una busqueda lineal dos veces. Y en contraste con este mapa, O(n)*O(1) = O(n). Lo cual es bastante mejor.

---

Sobre las operaciones de recuperar acciones pasadas, implentamos una pila hecha con un arreglo circular, que guarda lo siguiente:

- id del tipo de accion.
- informacion que hay que restaurar.

De esta forma ahorramos espacio, al solo guardar datos que cambiaron, y no toda la informacion de el sistema.
La forma en la que esto funciona es la siguiente. Cada vez que se realiza una accion, como por ejemplo agregar item, eliminarlo, agregar puntos. Se guarda la informacion antes de ser modificada en la pila junto al tipo de modificacion. Luego al llamar la funcion que deshace, se analiza el id, y gracias a eso realizamos operaciones inversas para restaurar el estado anterior de el jugador.

Esto si bien consideramos ventajoso, como se menciono, para el ahorro de memoria. Podria no resultar tan rapido como otros metodos, sin embargo, gracias a que como mencionamos las operaciones de mapa son muy rapidas, no consideramos que sea una perdida muy grande.
 
 ---


Rubrica Trabajo en equipo:

-    Participacion activa y equitativa: 15

-    Resolucion de conflictos:18

-    Colaboración:18

-    Responsabilidad:18

-    Comunicación:18

Criterio individual:

-    Participación:
-        Manuel: 20
-        Eliseo: 17
-        Felipe: 
-    Responsabilidad
-        Manuel: 18
-        Eliseo: 17
-        Felipe: 
-    Comunicación
-        Manuel: 20
-        Eliseo: 18
-        Felipe: 
-    Calidad del Trabajo
-        Manuel: 20
-        Eliseo: 18
-        Felipe: 
-    Trabajo en equipo
-        Manuel: 17
-        Eliseo: 17
-        Felipe: 
