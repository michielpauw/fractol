# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpauw <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/06 17:41:17 by mpauw             #+#    #+#              #
#    Updated: 2017/12/15 16:03:10 by mpauw            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
FLAGS = -Wall -Wextra -Werror 
INCLUDES = fractol.h
SRCS = fractol.c \
	   fractal_functions.c \
	   get_fractal.c \
	   window_control.c \
	   zoom_control.c \
	   image_functions.c \
	   setup_event.c \
	   mouse_event.c \
	   put_coordinates.c 
OBJ = $(SRCS:%.c=%.o)
LFTDIR = libft/
LMLXDIR = minilibx_macos/
LIBFT = libft.a
LIBMLX = libmlx.a
FT = ft
MLX = mlx
MAKE = make
FRAMEWORK = -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME): $(OBJ) $(LFTDIR)$(LIBFT) $(LMLXDIR)$(LIBMLX) 
	-@gcc $(FLAGS) -o $(NAME) -g $(OBJ) -I$(LFTDIR) -L$(LFTDIR) -l$(FT) \
		-L$(LMLXDIR) -l$(MLX) $(FRAMEWORK)
	-@echo "Fractol Ready"

%.o: %.c $(INCLUDES)
	-@gcc $(FLAGS) -I$(LFTDIR) -c $(SRCS)

$(LFTDIR)$(LIBFT):
	$(MAKE) -C $(LFTDIR) $(LIBFT)

$(LMLXDIR)$(LIBMLX):
	$(MAKE) -C $(LMLXDIR) $(LIBMLX)

clean:
	-@/bin/rm -f $(OBJ)
##	-@$(MAKE) -C $(LFTDIR) clean
##	-@$(MAKE) -C $(LMLXDIR) clean

fclean: clean
	-@/bin/rm -f $(NAME)
##	-@$(MAKE) -C $(LFTDIR) fclean

re: fclean all
