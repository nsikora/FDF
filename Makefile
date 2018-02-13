# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsikora <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/23 16:56:40 by nsikora           #+#    #+#              #
#    Updated: 2018/02/09 15:47:48 by nsikora          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

CC		=	/usr/bin/gcc

CFLAGS	=	-Wall -Wextra -Werror

OBJS	=	$(SRCS:.c=.o)

RM		=	/bin/rm -f

SRCS	=	main.c 					\
			ft_check_ext.c			\
			ft_key_event.c			\
			ft_display_dot.c		\
			ft_declare_data.c		\
			ft_parsing_init_data.c	\
			get_next_line.c			\

CPPFLAGS =	-I includes -I mlx -I libft

LIBFT = libft/libft.a
MLX = mlx/libmlx.a

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CPPFLAGS) -L ./libft -lft -L mlx -l mlx -framework OpenGl -framework Appkit

$(LIBFT):
	make -C libft
	
$(MLX):
	make -C mlx

%.o: %.c
	$(CC) -o $@ -c $< $(CPPFLAGS) $(CFLAGS)

clean:
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	make clean -C mlx
	$(RM) $(NAME)

re:	fclean all

.PHONY: all re clean fclean
