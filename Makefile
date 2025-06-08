CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
LIBFT = libft/libft.a
NAME = minishell

SRC =	main.c free_list.c env_init.c parsing/ft_error.c parsing/split_pipe.c \
    	env_help.c parsing/do_space.c parsing/parsing.c parsing/ft_error_pipe.c \
		parsing/ft_error_red.c parsing/ft_space_pipes.c parsing/parsing_utils.c \
		parsing/create_list1.c parsing/create_list2.c parsing/create_list3.c \
		builtins/ft_builtin.c builtins/ft_pwd.c builtins/ft_cd.c builtins/ft_echo.c \
		builtins/ft_env.c builtins/ft_exit.c builtins/ft_unset.c builtins/ft_export.c \
		builtins/export_helper.c builtins/export_helper2.c builtins/export_helper3.c \
		execution/ft_execution.c execution/path.c execution/exec_loop.c \
		execution/herdoc.c execution/ft_redirections.c execution/pipes_helpe.c \
		execution/exec_help.c execution/herdoc_help.c signals.c \
		expand/ft_expand.c expand/ft_expand_red.c expand/ft_split2.c \
		expand/ft_expand_helper1.c expand/ft_expand_helper2.c expand/ft_expand_helper3.c \
		

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME) 

$(LIBFT):
	@make -C libft

clean:
	@rm -f $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re

