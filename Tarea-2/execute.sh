#!bin/bash

printf "Compilando proyecto:\n"

gcc -w proyecto/Map.c proyecto/backend.c proyecto/main.c -o o.out

printf "\n Ejecutando..\n"

./o.out

printf "Ejecucion Terminada.\n"