NAME = opengl.dynlib
SRC = opengl.cpp
OBJ = opengl.o
COMPILER = clang++

INC = -I ../../include
DEP_DIR = ~/.brew/Cellar/glfw/3.3
DEP = -I ../../include -I $(DEP_DIR)/include/GLFW/ $(DEP_DIR)/lib/libglfw.3.3.dylib -framework OpenGL

all: $(NAME)

$(NAME): $(OBJ)
	@$(COMPILER) -w -dynamiclib -o $(NAME) $(OBJ) $(DEP) $(INC) ../../src/*

$(OBJ):
	@$(COMPILER) -w -c $(SRC) $(DEP)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all