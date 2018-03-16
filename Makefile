all: amigos

amigos: amigos.c amigos.o
	mpicc -o amigos amigos.c amigos.o

clean: rm amigos
	rm *.o