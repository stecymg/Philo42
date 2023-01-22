CC = cc

RM = rm -rf

NAME = philo

SRCS = philo.c\
		usleep.c\
		runtime.c\
		utils.c\
		init.c\
		free_all.c\
		main.c\
		death.c\
		life.c\
		error_msg.c\
		parsing.c\

MANDATORY_SRCS = ${MANDATORY}

MANDATORY_OBJS = ${MANDATORY_SRCS:.c=.o}

CFLAGS = -g -Wall -Wextra -Werror -fsanitize=thread

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${MANDATORY_OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${MANDATORY_OBJS} -lpthread

clean:
		${RM} ${MANDATORY_OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re