# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rouali <rouali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 20:23:47 by rouali            #+#    #+#              #
#    Updated: 2023/06/21 18:56:51 by rouali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = philo.c ft_atoi.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJ)

clean :
	rm -rf $(OBJ)

fclean :
	rm -rf $(NAME)

re : fclean all