
CC =	clang

CFLAGS =	-g -Wextra -Wall -I./MLX42/include/MLX42 -I./libft/include

LIBMLX	:= ./MLX42

LIBMLX_NAME = ./MLX42/build/libmlx42.a

LIBFT = libft/libft.a

BONUS_PATH = Bonus/srcs/

MANDATORY_PATH = Mandatory/srcs/

LIBFT_PATH = libft --no-print-directory

LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

NAME =	cub3D

NAME_BONUS = cub3D_bonus

BONUS = ${BONUS_PATH}Mlx/key_hook_bonus.c				\
		${BONUS_PATH}Mlx/manage_collision_bonus.c		\
		${BONUS_PATH}Parsing/ft_checkarg_bonus.c 		\
		${BONUS_PATH}Parsing/ft_checkmap_bonus.c		\
		${BONUS_PATH}Parsing/ft_get_cub_bonus.c			\
		${BONUS_PATH}Parsing/ft_get_rgb_from_id_bonus.c	\
		${BONUS_PATH}Parsing/ft_map_parsing_bonus.c		\
		${BONUS_PATH}Parsing/ft_parse_data_bonus.c		\
		${BONUS_PATH}Parsing/ft_parse_player_bonus.c	\
		${BONUS_PATH}Parsing/ft_parsing_main_bonus.c	\
		${BONUS_PATH}Parsing/ft_load_animation_bonus.c	\
		${BONUS_PATH}Parsing/ft_parse_door_bonus.c		\
		${BONUS_PATH}Utils/colors_bonus.c				\
		${BONUS_PATH}Utils/count_door_bonus.c			\
		${BONUS_PATH}Utils/empty_line_bonus.c			\
		${BONUS_PATH}Utils/exit_bonus.c					\
		${BONUS_PATH}Utils/free_bonus.c					\
		${BONUS_PATH}Utils/ft_draw_column_utils_bonus.c	\
		${BONUS_PATH}Utils/ft_raycast_get_bonus.c		\
		${BONUS_PATH}Utils/door_utils_bonus.c		\
		${BONUS_PATH}ft_draw_column_bonus.c				\
		${BONUS_PATH}ft_move_bonus.c					\
		${BONUS_PATH}Minimap/ft_draw_minimap_bonus.c	\
		${BONUS_PATH}Minimap/ft_printing_bonus.c		\
		${BONUS_PATH}Minimap/minimap_bonus.c			\
		${BONUS_PATH}Minimap/ft_fov_utils_bonus.c		\
		${BONUS_PATH}ft_raycast_bonus.c					\
		${BONUS_PATH}ft_rotate_bonus.c					\
		${BONUS_PATH}main_bonus.c						\


MANDATORY = ${MANDATORY_PATH}Mlx/key_hook.c				\
		${MANDATORY_PATH}Mlx/manage_collision.c			\
		${MANDATORY_PATH}Parsing/ft_checkarg.c 			\
		${MANDATORY_PATH}Parsing/ft_checkmap.c			\
		${MANDATORY_PATH}Parsing/ft_get_cub.c			\
		${MANDATORY_PATH}Parsing/ft_get_rgb_from_id.c	\
		${MANDATORY_PATH}Parsing/ft_map_parsing.c		\
		${MANDATORY_PATH}Parsing/ft_parse_data.c		\
		${MANDATORY_PATH}Parsing/ft_parse_player.c		\
		${MANDATORY_PATH}Parsing/ft_parsing_main.c		\
		${MANDATORY_PATH}Utils/colors.c					\
		${MANDATORY_PATH}Utils/empty_line.c				\
		${MANDATORY_PATH}Utils/exit.c					\
		${MANDATORY_PATH}Utils/free.c					\
		${MANDATORY_PATH}Utils/ft_draw_column_utils.c	\
		${MANDATORY_PATH}Utils/ft_raycast_get.c			\
		${MANDATORY_PATH}ft_draw.c						\
		${MANDATORY_PATH}ft_draw_column.c				\
		${MANDATORY_PATH}ft_move.c						\
		${MANDATORY_PATH}ft_raycast.c					\
		${MANDATORY_PATH}ft_rotate.c					\
		${MANDATORY_PATH}main.c							\

OBJ_MANDATORY = ${MANDATORY:.c=.o}

OBJ_BONUS = ${BONUS:.c=.o}

${NAME}: INCLUDES = -I./Mandatory/includes

${NAME_BONUS}: INCLUDES = -I./Bonus/includes

all: ${NAME}

$(LIBMLX_NAME):
	@cmake -DDEBUG=1 -DGLFW_FETCH=0 $(LIBMLX)  -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 ;

.c.o:
	@printf "Compiling .c to .o \r"
	@${CC} ${CFLAGS} ${INCLUDES} -c $< -o ${<:.c=.o} $(HEADERS)
	
$(NAME): ${LIBMLX_NAME} ${LIBFT} ${OBJ_MANDATORY}
	@${CC} ${CFLAGS} ${OBJ_MANDATORY} ${LIBFT} $(LIBS) $(HEADERS) -o ${NAME} 
	@printf '\e[1;37m'"Compilation complete"'\e[m''\n'

$(NAME_BONUS): ${LIBMLX_NAME} ${LIBFT} ${OBJ_BONUS}
	@${CC} ${CFLAGS} -I./Bonus/includes ${OBJ_BONUS} ${LIBFT} $(LIBS) $(HEADERS) -o ${NAME_BONUS} 
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

re_bonus: fclean bonus

.PHONY:	all clean fclean re libmlx bonus re_bonus
