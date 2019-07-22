NAME = nibbler

TARGET_DIR = ./bin/
TARGET = $(TARGET_DIR)$(NAME)

SDL_DIR = ~/.brew/Cellar/sdl2/2.0.9_1/

COMPILER = clang++
FLAGS = -w -Werror -Wextra -Wall -I include -I $(SDL_DIR)include
NCURSES_DEP = -l ncurses
OPENGL_DEP = -framework OpenGL -framework GLUT
SDL_DEP =  $(SDL_DIR)lib/libSDL2main.a $(SDL_DIR)lib/libSDL2.a -framework Metal -framework AudioToolbox -framework CoreVideo -framework Carbon -framework ForceFeedback -framework IOKit -framework Cocoa -framework CoreAudio -liconv -lm -Wl,-current_version,10.0.0 -Wl,-compatibility_version,1.0.0 -Wl,-undefined,error

COMPILE = $(COMPILER) $(FLAGS) $(NCURSES_DEP) $(OPENGL_DEP) $(SDL_DEP) 

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

SDL2: SDL2.tar.gz
	mkdir -p SDL2
	mkdir -p SDL2/build
	tar -xf SDL2.tar.gz -C SDL2 --strip-components 1
	cd SDL2
	make

SDL2.tar.gz:
	curl -o SDL2.tar.gz https://www.libsdl.org/release/SDL2-2.0.9.tar.gz