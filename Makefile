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

NAME				= so_long
HEADER		 		= SRC/so_long.h
HEADER_B		 	= SRC_B/so_long_bonus.h
SRCS				= SRC/main.c\
					SRC/moves.c\
					SRC/errors.c\
					SRC/read_map.c\
					SRC/free.c\
					SRC/render.c
SRCS_B				= SRC_B/main_bonus.c\
					SRC_B/moves_bonus.c\
					SRC_B/errors_bonus.c\
					SRC_B/read_map_bonus.c\
					SRC_B/free_bonus.c\
					SRC_B/render_bonus.c\
					SRC_B/load_files.c\
					SRC_B/valid_map_bonus.c
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
