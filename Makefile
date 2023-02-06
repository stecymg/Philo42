# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smontgen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 12:14:48 by smontgen          #+#    #+#              #
#    Updated: 2023/01/25 12:14:55 by smontgen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
		print_status.c\
		error_msg.c\
		parsing.c\

MANDATORY_SRCS = ${SRCS}

MANDATORY_OBJS = ${SRCS:.c=.o}

CFLAGS = -g -Wall -Wextra -Werror

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
