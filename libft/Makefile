# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wadina <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 01:49:44 by wadina            #+#    #+#              #
#    Updated: 2022/04/02 01:49:46 by wadina           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LH = libft.h

SRC =	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c\
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c\
		ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c\
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
		ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c  ft_substr.c\
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
		ft_lstmap.c get_next_line.c get_next_line_utils.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra
# CFLAGS+=-O2
# CFLAGS+= -DSTRINGPUTX11


CC = clang
AR = ar
ARFLAGS = -rcs

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ) $(LH) Makefile
	$(AR) $(ARFLAGS) $@ $(OBJ)
	# ranlib $(NAME)

%.o : %.c $(LH) Makefile
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
