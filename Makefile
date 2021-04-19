TARGET: ll.o libll.a tree.o libtree.a main.o main 

CC=gcc
#CFLAGS=-Wall -g -fno-stack-protector 
CFLAGS=-Wall -g
LDLIBS=

main: main.o
	${CC} ${CFLAGS} main.o -o main -L. -I. -lll -ltree

main.o: main.c
	${CC} ${CFLAGS} -c main.c -o main.o


ll.o: ll.c
	${CC} ${CFLAGS} -c ll.c -o ll.o

libll.a: ll.o
	ar crs libll.a ll.o

#tree.o: tree.c
#	${CC} ${CFLAGS} -c tree.c -fPIC -o tree.o
#
#libtree.so: tree.o
#	${CC} ${CFLAGS} -shared ll.o tree.o -o libtree.so

tree.o: tree.c
	${CC} ${CFLAGS} -c tree.c -o tree.o

libtree.a: tree.o
#	${CC} ${CFLAGS} ll.o tree.o -o libtree.so
	ar crs libtree.a tree.o

clean:
	rm ./*.o ./main ./*.a



