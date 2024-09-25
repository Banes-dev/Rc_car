COMP = c++

CFLAGS = -g -Wall -Wextra -Werror

# Normal
NAME = Rc_car
FUNC = main.cpp Servo.cpp
OBJS = ${FUNC:.cpp=.o}


# Compil
all: 	${NAME}

${NAME}: ${OBJS}
	${COMP} ${CFLAGS} ${OBJS} -o ${NAME}

clean:	
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re