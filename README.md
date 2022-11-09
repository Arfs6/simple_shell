# **HSH SHELL**  

This project is an attempt to model the sh shell (/bin/sh in unix machines). Only c language was used. System calls like fork, wait and execve were used.  

## **GETTING STARTED**  
To compile the shell, you can use make or compile using *.c. If you compile using make, the name of the executable will be hsh and it will be in the current directory. After compiling using make, some hidden object files will be in the current directory. Use make clean to delete it.  
```
$ make clean  
```

## **USAGE**  
The shell runs in two ways.  
1. Interactive mode: To run the shell in this mode, you need to run the executable without any arguments.  
   ```
   $ ./hsh
   ```
   In interactive mode, you can use the shell interactively. Use exit or C-d to exit.  
2. Execute mode: Running the shell executable with arguments will try running the arguments passed as an executable.  
       ```
      hsh /bin/ls -l /etc  
        ```
    First argument should be path to the executable, subsequent arguments will be passed as arguments to the executable. In the example above, */bin/ls* is the path to the executable the shell will run and *-l .* are the arguments the executable will get.  
