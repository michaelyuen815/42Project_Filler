# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chyuen <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/03 16:03:25 by chyuen            #+#    #+#              #
#    Updated: 2019/07/03 16:03:27 by chyuen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = chyuen.filler

DIRSRC = ./srcs/
DIRLIB = ./libft/
DIRHDER = ./includes/

all: $(NAME)

$(NAME):
	Make -C $(DIRLIB)
	gcc -Wall -Wextra -Werror \
	-o $(NAME) \
	$(DIRSRC)*.c \
	-I $(DIRHDER) \
	-L $(DIRLIB) -lft
	
clean:
	/bin/rm -f *.o
	Make clean -C $(DIRLIB)

fclean: clean
	/bin/rm -f $(NAME)
	Make fclean -C $(DIRLIB)

re: fclean all
