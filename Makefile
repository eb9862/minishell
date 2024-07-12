CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

NAME = minishell

HEADER = built_in.h minishell.h get_next_line.h

DIR_LIBFT = ./libft

SRCS =	built_in.c\
		built_in_utils.c\
		env_var.c\
		envp_list.c\
		excutor.c\
		file_close.c\
		file_handler.c\
		get_next_line.c\
		get_next_line_utils.c\
		line_handler.c\
		main.c\
		process_free.c\
		process_info_creator.c\
		process_info_utils.c\
		tokenizer_free.c\
		tokenizer_utils.c\
		tokenizer.c\
		validator_utils.c\
		validator.c


OBJS = $(SRCS:.c=.o)

MAKE = make

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(DIR_LIBFT) all
	$(CC) $(CFLAGS) -lreadline $^ -o $(NAME) -lm -lft -L $(DIR_LIBFT)

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
