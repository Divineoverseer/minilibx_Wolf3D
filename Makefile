# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmaltsev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/18 19:37:24 by dmaltsev          #+#    #+#              #
#    Updated: 2018/10/18 19:37:26 by dmaltsev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom_nukem

cc = gcc
C_FLAGS = -Wall -Wextra -Werror
FRAM = -lmlx -framework OpenGL -framework AppKit
DEPS = ./includes/doom_nukem.h

OBJ_PATH = ./obj/
LFT_PATH = ./libft/
INC_PATH = ./includes/
SRC_PATH = ./srcs/

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = doom_nukem.h
SRC_NAME = main.c ft_draw.c ft_construct.c ft_map_fixer.c ft_events.c

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LFT_PATH)
	$(CC) -o $(NAME) $(FRAM) -L $(LFT_PATH) -lft $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEPS)
	mkdir -p $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

clean:
	make -C $(LFT_PATH) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LFT_PATH) fclean
	rm -rf $(NAME)

re: fclean all