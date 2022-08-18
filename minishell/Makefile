# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/11 12:53:57 by klemongr          #+#    #+#              #
#    Updated: 2022/04/28 09:00:09 by klemongr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror

LIST =	cd.c			\
		commands.c		\
		env.c			\
		exit.c			\
		export.c		\
		excerpt_cmd.c	\
		execution.c		\
		execution_2.c	\
		free_ms.c		\
		ft_split.c		\
		ft_strjoin.c	\
		ft_strlen.c		\
		ft_strnstr.c	\
		get_next_line.c	\
		here_doc.c		\
		history.c		\
		main.c			\
		my_func.c		\
		open_file.c		\
		parsing.c		\
		parsing_2.c		\
		path_func.c		\
		pipes.c			\
		read_cmd.c		\
		redirections.c	\
		unset.c			\
		variables.c		\

OBJSFD = temporary

OBJ = $(addprefix $(OBJSFD)/,$(LIST:.c=.o))

all : $(NAME)

$(OBJSFD):
	mkdir $@

$(OBJSFD)/%.o: %.c | $(OBJSFD)
	gcc -g $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	gcc -g $(OBJ) -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re