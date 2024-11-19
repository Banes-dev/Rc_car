COMP = c++

CFLAGS = -g -Wall -Wextra -Werror

# Normal
NAME = Client
FUNC = main.cpp nRF24L01.cpp
OBJS = ${FUNC:.cpp=.o}


# Compil
all: 	${NAME}

${NAME}: ${OBJS}
	${COMP} ${CFLAGS} ${OBJS} -o ${NAME} -lrf24

%.o: %.cpp
	${COMP} ${CFLAGS} -c $< -o $@

clean:	
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re