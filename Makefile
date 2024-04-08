##
## EPITECH PROJECT, 2024
## Groundhog
## File description:
## Makefile
##

EXEC   =    groundhog

all:   $(EXEC)

$(EXEC):    $(OBJ)
	g++ -o $(EXEC) Groundhog.cpp main.cpp -g3

clean:
	rm -f $(EXEC)

fclean: clean
	rm -f $(EXEC)

re: fclean all