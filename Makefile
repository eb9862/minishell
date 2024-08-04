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
		process_handler_utils.c\
		process_handler_utils2.c\
		built_in_handler.c\
		minishell_test_utils.c\
		quotes_handler.c\
		line_expand_manager.c\
		line_expand_manager_utils.c\
		double_quotes_handler.c\
		double_quotes_handler_utils.c\
		double_quotes_handler_utils_2.c\
		double_quotes_handler_utils_3.c\
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
		heredoc_handler_utils.c\
		process_create_manager.c\
		process_create_utils.c\
		plain_handler.c\
		signal_handler.c\
		heredoc_signal_handler.c\
		process_handler_errmsg.c\

OBJS = $(SRCS:.c=.o)

MAKE = make

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(DIR_LIBFT) all
	$(MAKE) -C $(DIR_GNL) all
	$(MAKE) -C $(DIR_BI) all
	$(CC) $(CFLAGS)  $^ -o $(NAME)  -lgnl -L $(DIR_GNL) -lbi -L $(DIR_BI)  -lft -L $(DIR_LIBFT) -lreadline -L/opt/homebrew/opt/readline/lib
#-L/usr/local/opt/readline/lib
#-L/usr/lib/x86_64-linux-gnu

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I/opt/homebrew/opt/readline/include
#-I/usr/local/opt/readline/include
#-I/usr/include/readline

export LDFLAGS="-L/opt/homebrew/opt/readline/lib"
  export CPPFLAGS="-I/opt/homebrew/opt/readline/include"

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
