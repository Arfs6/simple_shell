flags = -Wall -Werror -Wextra -pedantic -std=gnu89
objects = .functions0.o .strings.o .get.o .put.o .main.o .execute.o \
	  .linklist.o .print.o .commands.o .functions1.o

hsh: $(objects)
	gcc -o hsh $(objects)

.main.o: main.c main.h
	gcc -c $(flags) main.c -o .main.o
.execute.o: execute.c main.h
	gcc -c $(flags) execute.c -o .execute.o
.get.o: get.c main.h
	gcc -c $(flags) get.c -o .get.o
.commands.o: commands.c main.h
	gcc -c $(flags) commands.c -o .commands.o
.functions0.o: functions0.c main.h
	gcc -c $(flags) functions0.c -o .functions0.o
.strings.o: strings.c main.h
	gcc -c $(flags) strings.c -o .strings.o
.put.o: put.c main.h
	gcc -c $(flags) put.c -o .put.o
.linklist.o: linklist.c main.h
	gcc -c $(flags) linklist.c -o .linklist.o
.print.o: print.c main.h
	gcc -c $(flags) print.c -o .print.o
.functions1.o: functions1.c main.h
	gcc -c $(flags) functions1.c -o .functions1.o

clean:
	rm -rf *.o
