NAME = ncurses.lib

TARGET_DIR = ./
TARGET = $(TARGET_DIR)$(NAME)

COMPILER = clang++
FLAGS = -w -Werror -Wextra -Wall -I../../include

SRC = Graphics.cpp
OBJ = Graphics.o

all: $(NAME)

$(NAME): $(OBJ)
	@echo "COMPILING NCURSES"
	@$(COMPILER) -shared -fPIC -lncurses $(OBJ) -o $(TARGET)
	@echo "DONE"

$(OBJ):
	@echo "COMPILING OBJECT NCURSES"
	@$(COMPILER) $(FLAGS) -c $(SRC)
	@echo "DONE"


clean:
	@echo "CLEAN NCURSES"
	@rm -f $(OBJ)

fclean: clean
	@echo "FULL CLEAN NCURSES"
	@rm -f $(TARGET)

re: fclean all