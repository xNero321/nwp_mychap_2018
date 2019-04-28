##
## EPITECH PROJECT, 2017
## NWP_mychap_2018
## File description:
## Makefile
##

.PHONY: clean fclean re

NAME	=	client

CFLAGS	+= -I ./includes/ -g3

SRCS	=	./src/main.c	\
		./src/socket_init.c	\
		./src/error_handling.c	\
		./src/headers.c	\
		./src/hash.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./includes/

LIBRARIES += -lcrypto

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) $(LIBRARIES) -o $(NAME) $(LDFLAGS)
		rm $(OBJS)

tests_run: $(SRCS_TEST)
	$(CC) $(SRCS_TEST) $(SRCS) -I./includes -o units --coverage -lcriterion
	./units

wc:
	wc $(SRCS) ./includes/*

ta:
	make re
	./bonus/test_auto.sh
	make fclean

clean:
	$(RM) $(OBJS) *.g*

fclean: clean
	$(RM) $(NAME) units

re: fclean all

print_tests:
	lcov --directory ./ -c -o rapport.info
	genhtml -o ./report -t "code coverage report" rapport.info
	xdg-open ./report/index.html &>/dev/null
