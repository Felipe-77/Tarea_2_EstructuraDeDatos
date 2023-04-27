#!bin/bash

printf "Compilando proyecto:\n"

#cd /home/runner/Tarea-2/Tarea_2_EstructuraDeDatos

gcc -w HashMap/hashmap.c backend.c ArrayList/arraylist.c main.c -o o.out

printf "\n Ejecutando..\n"

./o.out

printf "Ejecucion Terminada.\n"
