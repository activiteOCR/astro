
VPATH = src:../inc

astro: main.o admin.o
	gcc main.o admin.o -o astro -Wall

main.o: main.c admin.h
	gcc -c main.c -Wall

admin.o: admin.c admin.h
	gcc -c admin.c -Wall

clean:
	rm -rf *.o

deepclean:
	rm -rf *.o main
