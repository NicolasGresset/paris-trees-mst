gcc -o testCorres.o -c testCorres.c -g
gcc -o testCorres testCorres.o ../../obj/fonctions.o ../../obj/parse.o ../../obj/manageSIGINT.o -lm -g
