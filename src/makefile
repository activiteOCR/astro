
VPATH = src:../inc

astro: main.o admin.o user.o
	gcc main.o admin.o user.o -o astro -Wall

main.o: main.c main.h admin.h user.h
	gcc -c main.c -Wall

admin.o: admin.c admin.h user.h main.h
	gcc -c admin.c -Wall

user.o: user.c user.h admin.h main.h
	gcc -c user.c -Wall

clean:
	rm -rf *.o

deepclean:
	rm -rf *.o main
