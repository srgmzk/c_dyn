#TARGET: ll.o libll.a tree.o libtree.a main.o main 
TARGET: spot.o spot 

CC=gcc
#CFLAGS=-Wall -g -fno-stack-protector 
CFLAGS=-Wall -g
LDLIBS=

spot: spot.o
	${CC} ${CFLAGS} spot.o -o spot -L./src/lib -I./src/include ./src/lib/libtermbox.a

spot.o: spot.c
	${CC} ${CFLAGS} -c spot.c -o spot.o

#tree.o: tree.c
#	${CC} ${CFLAGS} -c tree.c -o tree.o
#
#libtree.a: tree.o
#	${CC} ${CFLAGS} ll.o tree.o -o libtree.so
#	ar crs libtree.a tree.o

clean:
	rm ./*.o ./spot



