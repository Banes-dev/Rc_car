COMPIL = gcc
FLAGS = -Wall -Wextra -Werror

NAME = rc_car.a

FILE = control_ps4.c

OBJS = ${FILE:.c=.o}

.c.o:
		${COMPIL} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		ar -rsc ${NAME} ${OBJS}

all: 	${NAME}

clean:	
		rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re