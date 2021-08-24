SRC_C	=	client/main.c
SRC_S	=	server/main.c
UTILS	=	utils/ft_atoi.c utils/ft_bzero.c utils/ft_putnbr_fd.c utils/ft_putstr_fd.c utils/ft_strlen.c
NAME	=	minitalk
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
CLIENT	=	client/client
SERVER	=	server/server
INCLD	=	minitalk.h utils/utils.h

.PHONY		:	all re clean fclean minitalk bonus

all			:	$(NAME)

$(NAME)		:	$(CLIENT) $(SERVER)

$(CLIENT)	:	$(SRC_C) $(UTILS) $(INCLD)
				$(CC) $(CFLAGS) $(SRC_C) $(UTILS) -o $(CLIENT)

$(SERVER)	:	$(SRC_S) $(UTILS) $(INCLD)
				$(CC) $(CFLAGS) $(SRC_S) $(UTILS) -o $(SERVER)

clean		:
				rm -f $(CLIENT) $(SERVER)

fclean		:	clean

re			:	fclean all

bonus		:	all


