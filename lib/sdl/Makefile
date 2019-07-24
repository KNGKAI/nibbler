NAME = sdl.dynlib
SRC = sdl.cpp
OBJ = sdl.o
COMPILER = clang++

INC = -I ../../include
DEP_DIR = ~/.brew/Cellar/sdl2/2.0.9_1
DEP_INC = -I $(DEP_DIR)/include
DEP = $(DEP_DIR)/lib/libSDL2main.a $(DEP_DIR)/lib/libSDL2.a -framework Metal -framework AudioToolbox -framework CoreVideo -framework Carbon -framework ForceFeedback -framework IOKit -framework Cocoa -framework CoreAudio -liconv -lm -Wl,-current_version,10.0.0 -Wl,-compatibility_version,1.0.0 -Wl,-undefined,error

all: $(NAME)

$(NAME): $(OBJ)
	@$(COMPILER) -w -dynamiclib -o $(NAME) $(OBJ) $(DEP) $(INC) ../../src/*

$(OBJ):
	@$(COMPILER) -w -c $(SRC) $(DEP_INC)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all