# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 20:28:41 by arlarzil          #+#    #+#              #
#    Updated: 2024/01/29 15:39:20 by arlarzil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_COMMON_DIR 		=	src/
SRC_NORMAL_DIR	=	src/normal/
SRC_BONUS_DIR	=	src/bonus/

SRC_COMMON 		=	ft_split			\
					ft_strdup			\
					ft_strlen			\
					ft_strnstr			\
					ft_strjoin			\
					exec				\
					parse_env			\
					parse_command		\
					count_chars			\
					quote_type			\
					ft_isspace			\
					remove_quotes		\

SRC_NORMAL		=	main				\
					print_err			\
					test_file_access	\

SRC_BONUS 		=	main				\
					pipe_manip			\
					exit				\
					classic				\
					heredoc				\
					bonus_exec			\
					read_till_keyword	\
					get_next_line		\

SRC_TO_FILENAME_COMMON		= $(addsuffix .c, $(addprefix $(SRC_COMMON_DIR), $(SRC_COMMON)))
SRC_TO_FILENAME_NORMAL		= $(addsuffix .c, $(addprefix $(SRC_NORMAL_DIR), $(SRC_NORMAL)))
SRC_TO_FILENAME_BONUS		= $(addsuffix .c, $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS)))

OBJ_COMMON		=	$(SRC_TO_FILENAME_COMMON:.c=.o)
OBJ_NORMAL		=	$(SRC_TO_FILENAME_NORMAL:.c=.o)
OBJ_BONUS		=	$(SRC_TO_FILENAME_BONUS:.c=.o)

OBJS			=	$(OBJ_COMMON) $(OBJ_NORMAL) $(OBJ_BONUS)
OBJS_BONUS		=	$(OBJ_COMMON) $(OBJ_BONUS)
OBJS_NORMAL		=	$(OBJ_COMMON) $(OBJ_NORMAL)

NAME 			= 	pipex

BONUS_NAME		= 	pipex

CC 	= cc

CFLAGS 	= -Wall -Wextra -Werror -Icommon -g3

all: 	$(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS_NORMAL)
	$(CC) -o $(NAME) $(OBJS_NORMAL) $(CFLAGS)

bonus: $(OBJS_BONUS)
	$(CC) -o $(BONUS_NAME) $(OBJS_BONUS) $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

auteur:
	echo $(USER) > auteur

.PHONY: fclean all re clean
