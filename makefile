flags = -Wall -Werror -Wextra -pedantic -std=gnu89
objects = functions.o strings.o getcmd.o put.o test.o

hsh: $(objects)
	gcc -o hsh $(objects)

functions.o: functions.c main.h
	gcc -c $(flags) functions.c -o functions.o
strings.o: strings.c main.h
	gcc -c $(flags) strings.c -o strings.o
getcmd.o: getcmd.c main.h
	gcc -c $(flags) getcmd.c -o getcmd.o
put.o: put.c main.h
	gcc -c $(flags) put.c -o put.o
test.o: test.c main.h
	gcc -c $(flags) test.c -o test.o

clean:
	rm -rf *.o
