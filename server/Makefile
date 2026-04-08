COMP = c++

CFLAGS = -g -Wall -Wextra -Werror

# Normal
NAME = Server
FUNC = main.cpp Servo.cpp Controller.cpp nRF24L01.cpp
OBJS = ${FUNC:.cpp=.o}


# Compil
all: 	${NAME}

# For wiringPi = -lwiringPi; for pigpio = -lpigpio -lrt -lpthread
${NAME}: ${OBJS}
	${COMP} ${CFLAGS} ${OBJS} -o ${NAME} -lpigpio -lrt -lpthread -lSDL2 -lrf24

%.o: %.cpp
	${COMP} ${CFLAGS} -c $< -o $@

clean:	
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re