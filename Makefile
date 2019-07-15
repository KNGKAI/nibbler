NAME = nibbler

TARGET_DIR = ./bin/
TARGET = $(TARGET_DIR)$(NAME)

COMPILER = clang++
FLAGS = -w -Werror -Wextra -Wall
FRAMEWORKS = -framework OpenGL -framework GLUT -lncurses
COMPILE = $(COMPILER) $(FLAGS) $(FRAMEWORKS)

all: $(NAME)

$(NAME):
	@echo "COMPILING"
	@$(COMPILE) main.cpp -o $(TARGET)
	@echo "DONE"

clean:
	@echo "CLEAN"
	@rm -f $(OBJ)

fclean: clean
	@echo "FULL CLEAN"
	@rm -f $(TARGET)

re: fclean all

run: re
	@echo "RUN"
	@echo "---"
	@$(TARGET)