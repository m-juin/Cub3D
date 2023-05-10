# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 15:23:54 by mjuin             #+#    #+#              #
#    Updated: 2023/05/10 13:09:39 by mjuin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =	clang

CFLAGS =	-g -Wextra -Wall -I./includes -I./MLX42/include/MLX42 -I./libft/include

LIBMLX	:= ./MLX42

LIBMLX_NAME = ./MLX42/build/libmlx42.a

LIBFT = libft/libft.a

LIBFT_PATH = libft --no-print-directory

LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

NAME =	cub3D

NAME_BONUS =	cub3D_bonus

COMMON = srcs/main.c						\
		srcs/Utils/exit.c					\
		srcs/Utils/free.c					\
		srcs/Utils/colors.c					\
		srcs/Utils/empty_line.c 			\
		srcs/Utils/ft_draw_column_utils.c	\
		srcs/Utils/ft_raycast_get.c			\
		srcs/Parsing/ft_checkarg.c			\
		srcs/Parsing/ft_get_cub.c			\
		srcs/Parsing/ft_parse_data.c		\
		srcs/Parsing/ft_get_rgb_from_id.c	\
		srcs/Parsing/ft_parsing_main.c		\
		srcs/Parsing/ft_map_parsing.c		\
		srcs/Parsing/ft_parse_player.c		\
		srcs/ft_raycast.c					\
		srcs/ft_draw.c						\
		srcs/ft_move.c						\
		srcs/ft_rotate.c					\
		srcs/ft_draw_column.c				\
		srcs/Mlx/key_hook.c					\
		srcs/Mlx/manage_collision.c			\

BONUS = $(COMMON)							\
		srcs/Bonus/ft_checkmap_bonus.c		\
		srcs/Bonus/ft_draw_minimap.c		\
		srcs/Bonus/ft_printing.c			\
		srcs/Bonus/minimap.c				\

MANDATORY =	$(COMMON)						\
		srcs/Parsing/ft_checkmap.c			\

OBJ_MANDATORY =	${MANDATORY:.c=.o}

OBJ_BONUS =	${BONUS:.c=.o}

all:	${LIBMLX_NAME} ${LIBFT} ${NAME}

$(LIBMLX_NAME):
	@cmake -DDEBUG=1 -DGLFW_FETCH=0 $(LIBMLX)  -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 ;

.c.o:
	@printf "Compiling .c to .o \r"
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} $(HEADERS)
	
$(NAME): ${OBJ_MANDATORY} includes/cub3d.h
	@${CC} ${CFLAGS} ${OBJ_MANDATORY} ${LIBFT} $(LIBS) $(HEADERS) -o ${NAME} 
	@printf '\e[1;37m'"Compilation complete"'\e[m''\n'

$(NAME_BONUS): ${OBJ_BONUS} includes/cub3d.h
	@${CC} ${CFLAGS} ${OBJ_BONUS} ${LIBFT} $(LIBS) $(HEADERS) -o ${NAME_BONUS} 
	@printf '\e[1;37m'"Compilation complete"'\e[m''\n'

$(LIBFT):
	@make -C ${LIBFT_PATH}

bonus: $(NAME_BONUS)

clean:
	@rm -rf $(LIBMLX)/build/
	@make clean -C ${LIBFT_PATH}
	@n=1; \
	for file in $(OBJ_MANDATORY); do \
		if test -e $$file; then \
			if [ $$n -eq 1 ]; then \
				printf "Cleaning .o files \n"; \
			fi; \
			n=$$((n + 1)); \
			rm $$file; \
		fi \
	done
	@n=1; \
	for file in $(OBJ_BONUS); do \
		if test -e $$file; then \
			if [ $$n -eq 1 ]; then \
				printf "Cleaning .o files \n"; \
			fi; \
			n=$$((n + 1)); \
			rm $$file; \
		fi \
	done

fclean:	clean
	@make fclean -C ${LIBFT_PATH}
	@n=1; \
	if test -e ${NAME}; then \
		if [ $$n -eq 1 ]; then \
			printf "Cleaning files\n"; \
		fi; \
		n=$$((n + 1)); \
		rm ${NAME}; \
	fi
	@n=1; \
	if test -e ${NAME_BONUS}; then \
		n=$$((n + 1)); \
		rm ${NAME_BONUS}; \
	fi
re:	fclean all

.PHONY:	all clean fclean re libmlx bonus
