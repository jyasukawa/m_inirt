CC					= cc
CFLAGS			= -Wall -Wextra -Werror
LIBFT_FLAGS	= -L ./libft -lft
MLX_FLAGS		= -L mlx -lmlx -framework OpenGL -framework AppKit

FILES				= minirt.c \
							minirt_utils.c \
							init_scene.c \
							rendering.c \
							raytrace.c \
							get_nearest_shape.c \
							intersection_test_utils.c \
							vec3_utils_1.c \
							vec3_utils_2.c \
							vec3_utils_3.c

SRCS				= $(addprefix $(SRCS_DIR), $(FILES))
OBJS				= $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

SRCS_DIR		= srcs/
OBJS_DIR		= objs/
INCS_DIR		= incs/

NAME				= miniRT

all:					${NAME}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c $(INCS_DIR)minirt.h
							@mkdir -p ${OBJS_DIR}
							${CC} ${CFLAGS} -I $(INCS_DIR) -c $< -o $@

${NAME}:			${OBJS}
							@make bonus -C libft
							@make -C mlx
							${CC} ${CFLAGS} ${OBJS} ${LIBFT_FLAGS} ${MLX_FLAGS} -o ${NAME}

clean: 
							@make fclean -C libft
							@make clean -C mlx
							rm -rf ${OBJS_DIR}

fclean:				clean
							rm -rf ${NAME}

re:						fclean all

.PHONY:				all clean fclean re 