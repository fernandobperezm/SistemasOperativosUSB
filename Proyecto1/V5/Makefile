default: clean main.o reset
	gcc -Wall --debug -DTEST -o friendfindProcesos main.o
main.o: mainProcesos9.c
	gcc -Wall --debug -DTEST -c mainProcesos9.c -o main.o
clean:
	rm -f *.o
reset:
	reset
