all: lab2.exe

lab2.exe: lab2.c lib.c
		gcc lab2.c -c -g
		gcc lab2.o lib.o -o lab2.exe

lib.c:
	gcc ../lib/lib.c -c -g

clean:
		rm lab2.exe
		rm *.o