NAME = avm

CC = g++

#CFLAGS = -Wall -Wextra -Werror
CFLAGS = 

MFLAGS =

DIR_OBJ = ./obj/

SRC_DIR = ./src/class/

MAIN = main.cpp

FILES = lexer.class.cpp \
		parser.class.cpp \
		vm.class.cpp \
		AvmException.class.cpp \
		OperandFactory.class.cpp

INCLUDE_DIR = ./include

OBJ = $(patsubst %.cpp, $(DIR_OBJ)%.o, $(FILES)) $(patsubst %.cpp, $(DIR_OBJ)%.o, $(MAIN))

DEP_OBJ = src_msg \
		  $(OBJ)

RM = /bin/rm -rf

all: $(NAME)

$(NAME): mkdirobj $(DEP_OBJ)
		@ /bin/echo -n "Archiving object in $(NAME):"
		@ $(CC) -o $(NAME) $(OBJ) $(MFLAGS)
		@ echo " \033[32mAll done!\033[0m"

$(DIR_OBJ)%.o: $(SRC_DIR)%.cpp
	@ /bin/echo -n "    $(notdir $@)"
	@ $(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE_DIR)
	@ echo " \033[32mOK\033[0m"

mkdirobj:
	@ mkdir -p $(DIR_OBJ)

clean:
	@ /bin/echo -n "Removing object files:"
	@ $(RM) $(DIR_OBJ)
	@ echo " \033[32mdone\033[0m"

fclean: clean
	@ /bin/echo -n "Removing library:"
	@ $(RM) $(NAME)
	@ echo " \033[32mdone\033[0m"

re: fclean all

src_msg:
	@ echo " src functions:"

.PHONY : all clean fclean re
