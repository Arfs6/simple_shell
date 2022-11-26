   # **HSH SHELL**  

This project is an attempt to model the sh shell (/bin/sh in unix machines). Only c language was used. A lot of system calls like fork, wait and execve were used.  

## **INSTALLATION**  
There are no executable or installer releases for now. You need to compile the c source code manually. The recommended way to get the source code is by using git. Copy and paste the command below to clone the whole repo on your machine.
```
git clone https://github.com/arfs6/simple_shell
```
To compile the shell, you can use make or compile using gcc (or any c compiler). If you compile using make, the name of the executable will be hsh and it will be in the current directory. Paste the command below to compile the shell with make.
```
make
```
After compiling using make, some hidden object files will be in the current directory. Use make clean to delete it.  
```
 make clean  
```
If you are using windows, read this [article](https://www.technewstoday.com/install-and-use-make-in-windows/) on how to get the make utility on windows.  
Lastly. to compile using compilers, you can use
```
gcc *.c
```
if you already have gcc installed. All the .c files in the directory are for the shell, so you should add it all.  

## **USAGE**  
The shell runs in two ways.  
1. Interactive Mode: To run the shell in this mode, you need to run the executable without any arguments.
      ```
   ./hsh
      ```
   In interactive mode, you can use the shell interactively. Type any command and hit enter then the shell will execute it for you. A prompt '$' will be displayed after each executed command. Use exit or ctrl-d to exit.  
2. Non Interactive Mode: You can pipe a line separated commands to the shell and it will execute it line by line. Output will be printed in the current window and no prompt will be displayed. To start the shell this way, do
   ```
   echo "ls" | ./hsh
   ```
you can replace ls with any command.  

## **BUILTIN COMMANDS**  
For convenience, some built in commands are added to the shell. These are;  
* cd: most important! the cd command changes the working directory of the shell to the argument specified.
* env: The env command prints the environment variable to standard output.
* setenv: This command takes two argument, variable and value. It sets the variable in the environment variable.
* unsetenv: The unsetenv is the inverse of the setenv command. It unsets a variable in the environment variable. Only 1 argument is needed (i.e. variable name).
* exit: The exit command exits the shell.  
# **DEVELOPING...**  
The next feature been developed is the command separator. It will let you write several commands in one line.