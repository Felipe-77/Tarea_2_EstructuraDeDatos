#! /bin/bash

#The idea is to use this script in a git cloned repo
#because then git will be already set

printf "$1\n"



git add *
git commit -m "$1"

printf "\nLa contraseña es tu token de acceso\n"
git push

