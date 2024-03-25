# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: djoyke <djoyke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/20 15:38:33 by djoyke        #+#    #+#                  #
#    Updated: 2024/03/25 18:42:08 by dliu          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -Ofast -O3 -g -fsanitize=address

LIBFTDIR	= LIBFT
LIBFT		= $(LIBFTDIR)/libft.a
MLXDIR		= MLX42
MLX42		= $(MLXDIR)/build/libmlx42.a

HEADERS		= -I include -I $(MLXDIR)/include -I $(LIBFTDIR)/include
INCL		= -ldl -lglfw -pthread -lm
# ifeq ($(shell uname -m),arm64)
# INCL	= -framework Cocoa -framework OpenGL -framework IOKit -L "`brew --prefix glfw`/lib/" -lglfw
# else ifeq ($(shell uname -m),x86_64)
# INCL	= -framework Cocoa -framework OpenGL -framework IOKit -lglfw3
# endif

VPATH		= ./src ./src/utils ./src/map ./src/draw ./src/game
LIBS		= $(MLX42) $(LIBFT) $(INCL)
SRC			= 	main.c \
				utils.c \
				parse.c _parse_info.c _parse_grid.c _verify_grid.c \
				mlx.c

OBJDIR		= obj
OBJ			= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))


all:	$(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(MLX42):
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4 

$(LIBFT):
		@make -s -C $(LIBFTDIR)

$(OBJ): $(OBJDIR)/%.o : %.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c -o $@ $^ $(HEADERS)

clean:
		@make -s clean -C $(LIBFTDIR)
		@rm -rf $(OBJDIR)
		@rm -rf $(MLXDIR)/build

fclean: clean
		@make -s fclean -C $(LIBFTDIR)
		@rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re libmlx