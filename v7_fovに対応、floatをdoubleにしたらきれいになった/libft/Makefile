# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/05 14:14:16 by kousuzuk          #+#    #+#              #
#    Updated: 2023/12/05 14:14:23 by kousuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					= cc
CFLAGS			= -Wall -Wextra -Werror

SRCS				= ft_isalpha.c \
							ft_isdigit.c \
							ft_isalnum.c \
							ft_isascii.c \
							ft_isprint.c \
							ft_strlen.c \
							ft_memset.c \
							ft_bzero.c \
							ft_memcpy.c \
							ft_memmove.c \
							ft_strlcpy.c \
							ft_strlcat.c \
							ft_toupper.c \
							ft_tolower.c \
							ft_strchr.c \
							ft_strrchr.c \
							ft_strcmp.c \
							ft_strncmp.c \
							ft_memchr.c \
							ft_memcmp.c \
							ft_strnstr.c \
							ft_atoi.c \
							ft_calloc.c \
							ft_strdup.c \
							ft_strndup.c \
							ft_substr.c \
							ft_strjoin.c \
							ft_strtrim.c \
							ft_split.c \
							ft_itoa.c \
							ft_strmapi.c \
							ft_striteri.c \
							ft_putchar_fd.c \
							ft_putstr_fd.c \
							ft_putendl_fd.c \
							ft_putnbr_fd.c \
							ft_printf.c \
							ft_numbers_func.c \
							ft_words_func.c \
							get_next_line_bonus.c \
							get_next_line_utils_bonus.c \
							ft_printf_stderr.c \
							ft_numbers_func_stderr.c \
							ft_words_func_stderr.c

SRCS_BONUS	= ft_lstnew.c \
							ft_lstadd_front.c \
							ft_lstsize.c \
							ft_lstlast.c \
							ft_lstadd_back.c \
							ft_lstdelone.c \
							ft_lstclear.c \
							ft_lstiter.c \
							ft_lstmap.c

OBJS				= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)
HEADER			= libft.h
NAME				= libft.a

ifdef BONUS
  SRCS += $(SRCS_BONUS)
  OBJS += $(OBJS_BONUS)
endif

all:					${NAME}

$(NAME):			${OBJS}
							@ar -rcs $(NAME) ${OBJS}

bonus:				
							@$(MAKE) BONUS=1 all

%.o:					%.c $(HEADER)
							@$(CC) $(CFLAGS) -c $< -o $@

clean:
							@rm -f ${OBJS} ${OBJS_BONUS}

fclean:				clean
							@rm -f $(NAME)

re:						fclean all

.PHONY:				all bonus clean fclean re
