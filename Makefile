p1:
	gcc -o exe proyecto1.c `pkg-config --cflags --libs gtk+-3.0` -rdynamic

p2:
	gcc proyecto2.c -o exe

