# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/18 15:05:45 by mjuli             #+#    #+#              #
#    Updated: 2020/12/21 18:32:59 by mjuli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
FLAGS = -Wall -Wextra -Werror
LIBFT = -I libft -L libft -lft
SRC = \
	builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c \
	builtins/export.c builtins/pwd.c builtins/unset.c \
	env/env_init.c env/env_util.c env/var.c env/var_util.c \
	exec/command_util.c exec/command.c exec/exec.c \
	expansion/ex_quotes.c expansion/ex_var.c expansion/ex_var_util.c \
	parsing/arguments.c parsing/check.c \
	parsing/shell_split.c parsing/shell_strchr.c \
	redir/redir_rem.c redir/redir_util.c redir/redir.c \
	signals/signals.c \
	util/quote_check.c util/truncate.c util/util.c \
	main.c
OBJ = $(patsubst %.c, %.o, $(addprefix srcs/, $(SRC)))

all: $(NAME)

%.o: %.c
	gcc $(FLAGS) -c -o $@ $< -I libft -I includes

$(NAME): $(OBJ) includes/minishell.h
	cd libft && make
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	cd libft && make clean
	rm -f $(OBJ)

fclean: clean
	cd libft && make fclean
	rm -f $(NAME)

re: fclean all

