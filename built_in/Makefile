CC = cc

CFLAGS = -Wall -Werror -Wextra -g

NAME = libbi.a

HEADER = built_in.h

#DIR_LIBFT = ../libft

SRCS =	bi_cd.c\
		bi_echo.c\
		bi_env.c\
		bi_exit.c\
		bi_export_new.c\
		bi_pwd.c\
		bi_unset.c\
		built_in_utils.c\
		built_in_utils2.c\
		env_var.c\
		env_var2.c\
		env_var3.c\
		env_clear.c\
		#test_main.c

OBJS = $(SRCS:.c=.o)

MAKE = make

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $@ $^
#$(CC) $(CFLAGS) $^ -o $(NAME) -lft -L $(DIR_LIBFT)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
