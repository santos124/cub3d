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
HEADER		 		= src/cub3d.h
SRCS				= src/main.c\
					src/hooks.c\
					src/moves_dir.c\
					src/moves_left_right.c\
					src/errors.c\
					src/free.c\
					src/render.c\
					src/minimap.c\
					src/rays.c\
					src/parser/init_and_error.c\
					src/parser/map.c\
					src/parser/parse_player.c\
					src/parser/parse_tex_and_colors.c\
					src/parser/rec_map.c\
					src/parser/walls.c\
					src/parser/map_utils.c

OBJS				= ${SRCS:.c=.o}
CC					= clang
CFLAGS  			= -Wall -Wextra -Werror -g
LIBFTDIR			=	libft
LIBFT				=	$(LIBFTDIR)/libft.a
LIBMLXDIR			=	mlx
LIBMLX				=	$(LIBMLXDIR)/libmlx.a

all:		${NAME}

$(NAME)		:	$(OBJS) $(LIBFT) $(LIBMLX) $(HEADER) Makefile
			$(CC) $(CFLAGS)\
			-lmlx -framework OpenGL -framework Appkit\
			$(LIBFT) $(LIBMLX) $(OBJS) -o $(NAME)

$(LIBFT)	: Makefile $(LIBFTDIR)/libft.h $(LIBFTDIR)/Makefile
			make -C $(LIBFTDIR)

$(LIBMLX)	: Makefile $(LIBMLXDIR)/mlx.h $(LIBMLXDIR)/Makefile
			make -C $(LIBMLXDIR)

%.o			:	%.c Makefile $(HEADER) $(LIBFT) ./libft/*.c
			$(CC) $(CFLAGS) -c $< -o $@

re: 		fclean all

clean		:
			rm -f $(OBJS)
			make -C $(LIBFTDIR) clean
			make -C $(LIBMLXDIR) clean

fclean		:	clean
			rm -f $(LIBMLX)
			rm -f $(LIBFT)
			rm -f $(NAME)

.PHONY: 	all clean fclean re
