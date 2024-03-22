# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: djoyke <djoyke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/20 15:38:33 by djoyke        #+#    #+#                  #
#    Updated: 2024/03/22 19:16:35 by djoyke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
LIBFTDIR	= LIBFT
LIBFT		= $(LIBFTDIR)/libft.a
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -Ofast -O3
MLXDIR		= MLX42
MLX42		= $(MLXDIR)/build/libmlx42.a
HEADERS		= -I include/game -I include/utils -I $(MLXDIR)/include -I $(LIBFTDIR)/include
# INCL		= -ldl -lglfw -pthread -lm
ifeq ($(shell uname -m),arm64)
INCL	= -framework Cocoa -framework OpenGL -framework IOKit -L "`brew --prefix glfw`/lib/" -lglfw
else ifeq ($(shell uname -m),x86_64)
INCL	= -framework Cocoa -framework OpenGL -framework IOKit -lglfw3
endif
VPATH		= ./src
LIBS		= $(MLX42) $(LIBFT) $(INCL)
SRC			= 	main.c \
				utils/utils.c

OBJDIR		= obj
OBJ			= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))


all:	$(NAME)

$(NAME): $(LIBFT) $(OBJ) $(MLX42)
		$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(MLX42):
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4 

$(LIBFT):
		@make -s -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(VPATH)/%.c
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