**simple_shell**  
===========

This project is an attempt to model the sh shell (/bin/sh in unix machines).
The only language used was C. System calls like fork, wait and execve were used.
The contributors to the project are:  
* Abdulqadir Ahmad  
* nzube Ifechukwu  

To compile the shell, you can use make or compile using *.c. If you compile
using make, the name of the executable will be hsh and it will be in the
current directory.  

The shell runs in two ways.  
* Interactive mode: To run the shell in this mode, you need to run the
  executable without any arguments.  
>>		./hsh  
