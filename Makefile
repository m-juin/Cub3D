# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjuin <mjuin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 15:23:54 by mjuin             #+#    #+#              #
#    Updated: 2023/04/12 11:30:00 by mjuin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =	clang

CFLAGS =	-g -Werror -Wextra -Wall -I./includes -I./MLX42/include/MLX42

LIBMLX	:= ./MLX42

LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

NAME =	cub3D

SRC =	srcs/main.c

OBJ =	${SRC:.c=.o}

all:	libmlx ${NAME}

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

.c.o:
	@printf "Compiling .c to .o \r"
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} $(HEADERS)
	
$(NAME): ${OBJ}
	@${CC} ${CFLAGS} ${OBJ} $(LIBS) $(HEADERS) -o ${NAME} 
	@printf '\e[1;37m%-6s\e[m' "Compilation complete"

clean:
	@rm -rf $(LIBMLX)/build
	@n=1; \
	for file in $(OBJ); do \
		if test -e $$file; then \
			if [ $$n -eq 1 ]; then \
				printf "Cleaning .o files \n"; \
			fi; \
			n=$$((n + 1)); \
			rm $$file; \
		fi \
	done

fclean:	clean
	@n=1; \
	if test -e ${NAME}; then \
		if [ $$n -eq 1 ]; then \
			printf "Cleaning files\n"; \
		fi; \
		n=$$((n + 1)); \
		rm ${NAME}; \
	fi

re:	fclean all

.PHONY:	all clean fclean re libmlx
