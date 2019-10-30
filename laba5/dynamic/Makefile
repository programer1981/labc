dynamic: main.c ink.c delem.c
	gcc -fPIC -c ink.c
	gcc -fPIC -c delem.c
	gcc -shared ink.o delem.o -o libmyfunc.so
	gcc -c main.c
	gcc main.o -ldl -o  dynamic
clean:
	rm -f main.o ink.o delem.o res libmyfunc.so