CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

NAME = test

HEADER = built_in.h minishell.h

#DIR_GNL = gnl

DIR_LIBFT = ./libft

SRCS =	built_in.c\
		built_in_utils.c\
		env_var.c\

OBJS = $(SRCS:.c=.o)

MAKE = make

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(DIR_LIBFT) all
	$(CC) $(CFLAGS) $^ -o $(NAME) -lm -lft -L $(DIR_LIBFT)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean :
	$(MAKE) -C $(DIR_LIBFT) clean
	rm -rf $(OBJS)

fclean : clean
	$(MAKE) -C $(DIR_LIBFT) fclean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
