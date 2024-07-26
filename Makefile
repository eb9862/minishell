CC = cc

CFLAGS = -Wall -Werror -Wextra -g3

NAME = minishell

HEADER = minishell.h

DIR_LIBFT = ./libft

DIR_GNL = ./gnl

DIR_BI = ./built_in

SRCS =	line_handler.c\
		main.c\
		process_free.c\
		process_handler.c\
		minishell_test_utils.c\
		quotes_handler.c\
		line_expand_manager.c\
		line_expand_manager_utils.c\
		double_quotes_handler.c\
		double_quotes_handler_utils.c\
		line_expand_clear.c\
		single_quotes_manager.c\
		single_quotes_manager_utils.c\
		redirection_manager.c\
		space_handler.c\
		token_list_validator.c\
		token_list_validator_utils.c\
		file_manager.c\
		file_error_handler.c\
		heredoc_handler.c\
		process_create_manager.c\
		process_create_utils.c\
		plain_handler.c\
		signal_handler.c # test

OBJS = $(SRCS:.c=.o)

MAKE = make

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(DIR_LIBFT) all
	$(MAKE) -C $(DIR_GNL) all
	$(MAKE) -C $(DIR_BI) all
	$(CC) $(CFLAGS) -lreadline -L/usr/local/opt/readline/lib $^ -o $(NAME) -lft -L $(DIR_LIBFT) -lgnl -L $(DIR_GNL) -lbi -L $(DIR_BI)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I/usr/local/opt/readline/include

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
