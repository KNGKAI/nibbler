NAME = nibbler

TARGET_DIR = ./bin/
TARGET = $(TARGET_DIR)$(NAME)


COMPILER = clang++
FLAGS = -w -Werror -Wextra -Wall -I include

SRC = src/Coord.cpp src/Game.cpp src/GraphicEngine.cpp src/Map.cpp src/Noise.cpp src/Player.cpp
OBJ = obj/Coord.o obj/Game.o obj/GraphicEngine.o obj/Map.o obj/Noise.o obj/Player.o

all: $(NAME)

$(NAME): $(OBJ)
	@echo "COMPILING MAIN"
	@$(COMPILER) -w main.cpp -o $(TARGET) $(OBJ) $(FLAGS)
	@echo "DONE"
	@echo "COMPILING LIBS"
	@make -C lib/ncurses
	@make -C lib/opengl
	@make -C lib/sdl
	@echo "DONE"

$(OBJ):
	@echo "COMPILING OBJECTS"
	@$(COMPILER) -w -c $(SRC) $(FLAGS)
	@mkdir -p obj
	@mv Coord.o Game.o GraphicEngine.o Map.o Noise.o Player.o ./obj
	@echo "DONE"

clean:
	@echo "CLEAN"
	@make -C lib/ncurses clean
	@make -C lib/opengl clean
	@make -C lib/sdl clean
	@rm -f $(OBJ)

fclean: clean
	@echo "FULL CLEAN"
	@make -C lib/ncurses fclean
	@make -C lib/opengl fclean
	@make -C lib/sdl fclean
	@rm -f $(TARGET)

re: fclean all

run: re
	@echo "RUN"
	@echo "---"
	@$(TARGET)

SH = curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh

install:
	sh -c "$(SH)"
	brew install glfw
	brew install sdl2