# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: djoyke <djoyke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/20 15:38:33 by djoyke        #+#    #+#                  #
#    Updated: 2024/03/11 22:48:20 by djoyke        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
LIBFTDIR	= LIBFT
LIBFT		= $(LIBFTDIR)/libft.a
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -Ofast -O3
MLXDIR		= MLX42
MLX42		= $(MLXDIR)/build/libmlx42.a
HEADERS		= -I include -I $(MLXDIR)/include -I $(LIBFTDIR)/include
# INCL		= -ldl -lglfw -pthread -lm
ifeq ($(shell uname -m),arm64)
INCL	= -framework Cocoa -framework OpenGL -framework IOKit -L "`brew --prefix glfw`/lib/" -lglfw
else ifeq ($(shell uname -m),x86_64)
INCL	= -framework Cocoa -framework OpenGL -framework IOKit -lglfw3
endif
VPATH		= ./src
LIBS		= $(MLX42) $(LIBFT) $(INCL)
SRC			= main.c \


OBJ	= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

OBJDIR	= obj

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJ) $(MLX42)
		$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(MLX42):
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4 

$(LIBFT):
		@$(MAKE) -C $(LIBFTDIR)

$(OBJDIR)/%.o: %.c
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c -o $@ $^ $(HEADERS)
		
$(OBJDIR)/%.o:
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c -o $@ $^

clean:
		@$(MAKE) clean -C $(LIBFTDIR)
		@rm -rf $(OBJDIR)
		@rm -rf $(MLXDIR)/build

fclean: clean
		@$(MAKE) fclean -C $(LIBFTDIR)
		@rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re libmlx