#Makefile
#17/10/2018
#Kevin Le - 19472960

CC = gcc
EXEC = TurtleGraphics
LM = -lm

CFLAGS = -Werror -Wall -pedantic -ansi -g

#Object files required for Standard/Simple/Debug
OBJ = Main.o FileIO.o RunCmd.o LinkedList.o effects.o
OBJsimple = Main.o FileIO.o RunCmdSimple.o LinkedList.o effects.o
OBJdebug = Main.o FileIODebug.o RunCmd.o LinkedList.o effects.o

#Special object files to be deleted
RM = FileIODebug.o RunCmdSimple.o  

#Object dependencies
FILEIO = FileIO.c FileIO.h RunCmd.h
RUNCMD = RunCmd.c RunCmd.h LinkedList.h effects.h
LINKEDLIST = LinkedList.c LinkedList.h 
EFFECTS = effects.c effects.h

#--------PROGRAM-EXECUTEABLES-----------------------------------------

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LM)

#White Background/ Black Foreground - Ignores Other Commands to change colour. 
TurtleGraphicsSimple: $(OBJsimple)
	$(CC) $(OBJsimple) -o $(EXEC) $(LM)

#Print Log Entries alongside Charizard Print. 
TurtleGraphicsDebug: $(OBJdebug)
	$(CC) $(OBJdebug) -o $(EXEC) $(LM)

#--------STANDARD-OBJECTS---------------------------------------------

Main.o: Main.c FileIO.h
	$(CC) -c $(CFLAGS) Main.c -o Main.o

FileIO.o: $(FILEIO)
	$(CC) -c $(CFLAGS) FileIO.c -o FileIO.o 

RunCmd.o: $(RUNCMD)
	$(CC) -c $(CFLAGS) RunCmd.c -o RunCmd.o $(LM)

LinkedList.o: $(LINKEDLIST)
	$(CC) -c $(CFLAGS) LinkedList.c -o LinkedList.o 

effects.o: $(EFFECTS)
	$(CC) -c $(CFLAGS) effects.c -o effects.o

#--------SIMPLE/DEBUG-OBJECTS-----------------------------------------

#FileIO with DEBUG flag - For TurtleGraphicsDebug
FileIODebug.o: $(FILEIO)
	$(CC) -c $(CFLAGS) FileIO.c -o FileIODebug.o -D DEBUG=1

#Simple RunCmd with SIMPLE flag - For TurtleGraphicsSimple
RunCmdSimple.o: $(RUNCMD)
	$(CC) -c $(CFLAGS) RunCmd.c -o RunCmdSimple.o -D SIMPLE=1 $(LM)

#--------OTHER UTILS-------------------------------------------------

clean:
	rm -f $(OBJ) $(RM) $(EXEC); tput sgr0;

#Resets terminal colour quickly and deletes logfile.
clear:
	tput sgr0; rm graphics.log; clear; 
	
valgrind: 
	valgrind ./TurtleGraphics charizard.txt
