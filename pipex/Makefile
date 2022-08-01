# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 13:28:05 by hjabbour          #+#    #+#              #
#    Updated: 2022/07/28 17:04:19 by hjabbour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BSNAME = pipex_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

INC = pipex.h

RM = rm -fr

SRCS =	Mandatory/ft_split.c Mandatory/ft_strjoin.c \
		Mandatory/pipex.c Mandatory/paths.c Mandatory/utils.c 

BSRCS = Bonus/ft_split_bonus.c \
		Bonus/ft_strjoin_bonus.c \
		Bonus/here_doc.c Bonus/paths_bonus.c \
		Bonus/pipex_bonus.c Bonus/utils_bonus.c \
		Bonus/execute.c

OBJS = ${SRCS:.c=.o}

BOBJS = ${BSRCS:.c=.o}

all: ${NAME}
	
${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

%.o: %.c ${INC}
	${CC} ${CFLAGS} -c $< -o $@

bonus: ${BSNAME}

${BSNAME}: ${BOBJS}
	${CC} ${CFLAGS} ${BOBJS} -o ${BSNAME}

clean:
	${RM} ${OBJS} ${BOBJS}

fclean: clean
	${RM} ${NAME} ${BSNAME}

re: fclean all

.PHONY: all re clean fclean bonus