TARGET: ll.o libll.a tree.o libtree.a ui.o libui.a main.o main 

CC=gcc
#CFLAGS=-Wall -g -fno-stack-protector 
CFLAGS=-Wall -g

SRC=src/
LDLIBS=

main: main.o
	${CC} ${CFLAGS} main.o -o main -L. -I./include -lui -lll -ltree -lui ./ui/src/lib/libtermbox.a -pthread

main.o: main.c
	${CC} ${CFLAGS} -c main.c -o main.o

libll.a: ll.o
	ar crs libll.a ll.o

ll.o: ${SRC}ll.c
	${CC} ${CFLAGS} -c ${SRC}ll.c -o ll.o


libui.a: ui.o
	ar crs libui.a ui.o

ui.o: ${SRC}ui.c
	${CC} ${CFLAGS} -c ${SRC}ui.c -o ui.o -L./ui/src/lib -I./ui/src/include

#tree.o: tree.c
#	${CC} ${CFLAGS} -c tree.c -fPIC -o tree.o
#
#libtree.so: tree.o
#	${CC} ${CFLAGS} -shared ll.o tree.o -o libtree.so

tree.o: ${SRC}tree.c
	${CC} ${CFLAGS} -c ${SRC}tree.c -o tree.o

libtree.a: tree.o
#	${CC} ${CFLAGS} ll.o tree.o -o libtree.so
	ar crs libtree.a tree.o

clean:
	rm ./*.o ./main ./*.a



