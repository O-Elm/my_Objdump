##
## EPITECH PROJECT, 2021
## nmobjdump
## File description:
## Makefile
##

NAME1	=	my_nm

NAME2	=	my_objdump

NAME 	=	$(NAME2) $(NAME1)

SRC1	=	nm/src/main.c	\

SRC2	=	objdump/src/printing.c	\
			objdump/src/objdump64.c	\
			objdump/src/objdump32.c	\
			objdump/src/main.c	\

OBJ1	=	$(SRC1:.c=.o)

OBJ2	=	$(SRC2:.c=.o)

objdump:	$(NAME2)

nm:			$(NAME1)

all:		$(NAME2) $(NAME1)

$(NAME1):	$(OBJ1)
		@echo -e "\033[3;34m"
		gcc -o $(NAME1) $(OBJ1)
		@echo "------------"
		@echo "| nm        |"
		@echo "------------"
		@echo -e "\033[0m"

$(NAME2):	$(OBJ2)
		@echo -e "\033[3;32m"
		gcc -o $(NAME2) $(OBJ2)
		@echo "--------------"
		@echo "| objdump     |"
		@echo "--------------"
		@echo -e "\033[0m"

CFLAGS += -g3 -Werror -Wextra -Wall -ansi -pedantic -std=gnu11

clean:
		rm -f  $(OBJ1) $(OBJ2)

fclean:		clean
		rm -f $(NAME1) $(NAME2)

re:		fclean all

.PHONY:		clean all fclean
