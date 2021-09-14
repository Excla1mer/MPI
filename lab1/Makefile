all: lab1.exe

lab1.exe: lab1.c lib.c
		gcc lab1.c -c -g
		gcc lab1.o lib.o -o lab1.exe

lib.c:
	gcc ../lib/lib.c -c -g

clean:
		rm lab1.exe
		rm *.o