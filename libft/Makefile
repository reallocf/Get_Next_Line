# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csummers <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/31 11:06:06 by csummers          #+#    #+#              #
#    Updated: 2016/10/31 11:06:08 by csummers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES_1 = ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove ft_memchr ft_memcmp ft_strlen ft_strdup ft_strcpy ft_strncpy ft_strcat ft_strncat ft_strlcat ft_strchr ft_strrchr ft_strstr ft_strnstr ft_strcmp ft_strncmp ft_atoi ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_toupper ft_tolower

FILES_2 = ft_memalloc ft_memdel ft_strnew ft_strdel ft_strclr ft_striter ft_striteri ft_strmap ft_strmapi ft_strequ ft_strnequ ft_strsub ft_strjoin ft_strtrim ft_strsplit ft_itoa ft_putchar ft_putstr ft_putendl ft_putnbr ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd

FILES_BONUS = ft_lstnew ft_lstdelone ft_lstadd ft_lstiter ft_lstdel ft_lstmap

FILES_PERSONAL = ft_putstrarr ft_strarrnew ft_strarrdel ft_strarrlen ft_realloc_c ft_realloc_s ft_pow

SRC_FILES = $(addsuffix .c,$(FILES_1)) $(addsuffix .c,$(FILES_2)) $(addsuffix .c,$(FILES_BONUS)) $(addsuffix .c,$(FILES_PERSONAL))

OBJ_FILES = $(addsuffix .o,$(FILES_1)) $(addsuffix .o,$(FILES_2)) $(addsuffix .o,$(FILES_BONUS)) $(addsuffix .o,$(FILES_PERSONAL))

HDR = -I./includes

LIB = -L. -lft

COMP_FLAGS = -Wall -Wextra -Werror

.PHONY: all clean

all: $(NAME)

$(NAME):
	gcc -c $(COMP_FLAGS) $(HDR) $(SRC_FILES)
	ar rc $(NAME) $(OBJ_FILES)

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
