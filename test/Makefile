NAME = avm
SRC = ./src/Factory.cpp ./src/Machine.cpp ./src/Operand.cpp
OBJ = ./obj/Factory.o ./obj/Machine.o ./obj/Operand.o
TARGET = ./bin/$(NAME)
COMPILER = clang++
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@echo "COMPILING TARGET"
	@$(COMPILER) $(FLAGS) main.cpp $(OBJ) -o $(TARGET)
	@echo "DONE"

$(OBJ):
	@echo "COMPILING LIB"
	@$(COMPILER) $(FLAGS) -c $(SRC)
	@mv ./Factory.o ./Machine.o ./Operand.o ./obj/

clean:
	@echo "CLEAN"
	@rm -f $(OBJ)

fclean: clean
	@echo "FULL CLEAN"
	@rm -f $(TARGET)

re: fclean all

run: re
	@$(TARGET)