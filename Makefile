# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: djoyke <djoyke@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/20 15:38:33 by djoyke        #+#    #+#                  #
#    Updated: 2024/04/09 13:58:40 by dliu          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -Ofast -O3 #-g -fsanitize=address

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

VPATH		= ./src ./src/utils ./src/parse .src/maths ./src/game ./src/render ./src/bonus

LIBS		= $(MLX42) $(LIBFT) $(INCL)
SRC			= 	main.c \
				parse.c _parse_info.c _parse_grid.c _verify_grid.c \
				start.c render.c raytrace.c move.c \
				draw_utils.c vector_utils.c math_utils.c
OBJ			= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJDIR		= obj

BONUS		=	cub3d_bonus
SRC_B		=	main.c \
				parse.c _parse_info.c _parse_grid.c _verify_grid.c \
				bonus_start.c bonus_move.c bonus_minimap.c\
				render.c raytrace.c \
				draw_utils.c vector_utils.c math_utils.c
OBJDIR_B	= obj_bonus
OBJ_B		= $(addprefix $(OBJDIR_B)/, $(SRC_B:.c=.o))


all:	$(NAME)

bonus: $(LIBFT) $(MLX42) $(OBJ_B)
		$(CC) $(CFLAGS) $(OBJ_B) $(LIBS) $(HEADERS_B) -o $(BONUS)

$(NAME): $(LIBFT) $(MLX42) $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

$(MLX42):
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4 

$(LIBFT):
		@make -s -C $(LIBFTDIR)

$(OBJ): $(OBJDIR)/%.o : %.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c -o $@ $^ $(HEADERS)

$(OBJ_B): $(OBJDIR_B)/%.o: %.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c -o $@ $^ $(HEADERS)

clean:
		@make -s clean -C $(LIBFTDIR)
		@rm -rf $(OBJDIR)
		@rm -rf $(OBJDIR_B)
		@rm -rf $(MLXDIR)/build

fclean: clean
		@make -s fclean -C $(LIBFTDIR)
		@rm -f $(NAME)
		@rm -f $(BONUS)

re:		fclean all

.PHONY: all bonus clean fclean re