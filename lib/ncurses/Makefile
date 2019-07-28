NAME = ncurses.dynlib
SRC = ncurses.cpp
OBJ = ncurses.o
COMPILER = clang++

INC = -I ../../include
DEP = -l ncurses

all: $(NAME)

$(NAME): $(OBJ)
	@$(COMPILER) -w -dynamiclib -o $(NAME) $(OBJ) $(DEP) $(INC) ../../src/*

$(OBJ):
	@$(COMPILER) -w -c $(SRC) $(INC)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all