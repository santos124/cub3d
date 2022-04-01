# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wadina <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 16:47:09 by wadina            #+#    #+#              #
#    Updated: 2022/01/06 16:47:14 by wadina           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= cub3d
HEADER		 		= SRC/cub3d.h
HEADER_B		 	= SRC_B/cub3d_bonus.h
SRCS				= SRC/main.c\
					SRC/hooks.c\
					SRC/moves_dir.c\
					SRC/moves_left_right.c\
					SRC/errors.c\
					SRC/read_map.c\
					SRC/free.c\
					SRC/render.c\
					SRC/minimap.c\
					SRC/rays.c\
					SRC/parser/init_and_error.c\
					SRC/parser/map.c\
					SRC/parser/parse_player.c\
					SRC/parser/parse_tex_and_color.c\
					SRC/parser/rec_map.c\
					SRC/parser/walls.c

OBJS				= ${SRCS:.c=.o}
OBJS_B				= ${SRCS_B:.c=.o}
CC					= clang
CFLAGS  			= -Wall -Wextra -Werror
LIBFTDIR			=	libft
LIBFT				=	$(LIBFTDIR)/libft.a
LIBMLXDIR			=	mlx
LIBMLX				=	$(LIBMLXDIR)/libmlx.a

ifdef WITH_BONUS
OBJ					= $(OBJS_B)
HEADER 				= $(HEADER_B)
else
OBJ					= $(OBJS)
endif

all:		${NAME}

$(NAME)		:	$(OBJ) $(LIBFT) $(LIBMLX) $(HEADER) Makefile
			$(CC) $(CFLAGS)\
			-lmlx -framework OpenGL -framework Appkit\
			$(LIBFT) $(LIBMLX) $(OBJ) -o $(NAME)

$(LIBFT)	: Makefile $(LIBFTDIR)/libft.h $(LIBFTDIR)/Makefile
			make -C $(LIBFTDIR)

$(LIBMLX)	: Makefile $(LIBMLXDIR)/mlx.h $(LIBMLXDIR)/Makefile
			make -C $(LIBMLXDIR)

%.o			:	%.c Makefile $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

re: 		fclean all

clean		:
			rm -f $(OBJS) $(OBJS_B)
			make -C $(LIBFTDIR) clean
			make -C $(LIBMLXDIR) clean

fclean		:	clean
			rm -f $(LIBMLX)
			rm -f $(LIBFT)
			rm -f $(NAME)

bonus: 		
			$(MAKE) WITH_BONUS=1

.PHONY: 	all clean fclean re bonus
