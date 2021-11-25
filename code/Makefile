#Variables
EXEC = vote
CC = gcc
CFLAGS = -Wall
SRC = $(wildcard *.c) #Tous les fichiers .c
OBJ = $(SRC:.c=.o) #Pareil que SRC mais .c -> .o

#Mieu pour pas avoir de problème de dépendances
all : $(EXEC)

#Compile les fichiers .o en executable
$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

#Compile tous les fichiers .c en ficher .c
%.o : %.c
	$(CC) -c $(SRC)

#Commande
clean :
	rm -f $(OBJ)

allclean : clean
	rm -f $(EXEC)
