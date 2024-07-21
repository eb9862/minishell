CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

NAME = minishell

HEADER = minishell.h

DIR_LIBFT = ./libft

DIR_GNL = ./gnl

DIR_BI = ./built_in

SRCS =	excutor.c\
		file_handler.c\
		file_handler_utils.c\
		line_handler.c\
		main.c\
		process_free.c\
		process_info_creator.c\
		process_handler.c\
		process_info_utils.c\
		tokenizer_free.c\
		tokenizer_utils.c\
		tokenizer.c\
		validator_utils.c\
		validator.c\
		minishell_test_utils.c\
		quotes_handler.c\
		line_expand_manager.c\
		line_expand_manager_utils.c\

OBJS = $(SRCS:.c=.o)

MAKE = make

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(DIR_LIBFT) all
	$(MAKE) -C $(DIR_GNL) all
	$(MAKE) -C $(DIR_BI) all
	$(CC) $(CFLAGS) -lreadline $^ -o $(NAME) -lft -L $(DIR_LIBFT) -lgnl -L $(DIR_GNL) -lbi -L $(DIR_BI)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean :
	$(MAKE) -C $(DIR_LIBFT) clean
	$(MAKE) -C $(DIR_GNL) clean
	$(MAKE) -C $(DIR_BI) clean
	rm -rf $(OBJS)

fclean : clean
	$(MAKE) -C $(DIR_LIBFT) fclean
	$(MAKE) -C $(DIR_GNL) fclean
	$(MAKE) -C $(DIR_BI) fclean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
