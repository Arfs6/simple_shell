flags = -Wall -Werror -Wextra -pedantic -std=gnu89
objects = functions.o strings.o getcmd.o put.o main.o execute.o \
	  printerror.o

hsh: $(objects)
	gcc -o hsh $(objects)

main.o: main.c main.h
	gcc -c $(flags) main.c -o main.o
execute.o: execute.c main.h
	gcc -c $(flags) execute.c -o execute.o
getcmd.o: getcmd.c main.h
	gcc -c $(flags) getcmd.c -o getcmd.o
functions.o: functions.c main.h
	gcc -c $(flags) functions.c -o functions.o
printerror.o: printerror.c main.h
	gcc -c $(flags) printerror.c -o printerror.o
strings.o: strings.c main.h
	gcc -c $(flags) strings.c -o strings.o
put.o: put.c main.h
	gcc -c $(flags) put.c -o put.o

clean:
	rm -rf *.o
