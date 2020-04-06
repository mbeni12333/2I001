C_FLAGS = -g -Wall 

all: guimpe_basic main

image.o : image.c
	gcc $(C_FLAGS) -c image.c

pgm_image.o : pgm_image.c
	gcc $(C_FLAGS) -c pgm_image.c

utilitaires_tableaux.o: utilitaires_tableaux.c
	gcc $(C_FLAGS) -c utilitaires_tableaux.c

tri_rapide.o: tri_rapide.c utilitaires_tableaux.c
	gcc $(C_FLAGS) -c tri_rapide.c

trans_image.o : trans_image.c tri_rapide.c
	gcc $(C_FLAGS) -c trans_image.c

main.o: main.c trans_image.c
	gcc $(C_FLAGS) -c main.c

noyau.o : noyau.c
	gcc $(C_FLAGS) -c noyau.c

pile_image_basic.o : pile_image_basic.c pile_image.h
	gcc $(C_FLAGS) -c pile_image_basic.c `pkg-config --cflags gtk+-2.0`

guimpe_callback.o : guimpe_callback.c
	gcc $(C_FLAGS) -c guimpe_callback.c `pkg-config --cflags gtk+-2.0`

guimpe.o : guimpe.c
	gcc $(C_FLAGS) -c guimpe.c `pkg-config --cflags gtk+-2.0`

main: main.o trans_image.o noyau.o image.o utilitaires_tableaux.o tri_rapide.o
	gcc $(C_FLAGS) -o main main.o trans_image.o image.o noyau.o utilitaires_tableaux.o tri_rapide.o -lm

guimpe_basic	: guimpe.o guimpe_callback.o image.o pgm_image.o trans_image.o noyau.o pile_image_basic.o tri_rapide.o utilitaires_tableaux.o
	gcc $(C_FLAGS) -o guimpe_basic guimpe.o guimpe_callback.o image.o pgm_image.o trans_image.o  noyau.o pile_image_basic.o tri_rapide.o utilitaires_tableaux.o `pkg-config --libs gtk+-2.0` -lm

clean	:
	rm -f *.o guimpe_basic main
