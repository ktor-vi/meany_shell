NAME = minishell


SRC = 	src/main.c       \
		src/utils.c          \
		src/check_command.c  \
		src/echo_command.c   \
		src/envs_commands.c  \
		src/build_envs.c     \
		src/export_unset.c   \
		src/env_utils.c      \
		src/exec_utils.c     \
		src/exec_helpers.c   \
		src/cd_command.c     \
		src/pwd_command.c    \
		src/populate.c       \
		src/piping.c         \

INC = includes/minishell.h

CC = cc

FLAGS =   -g -fsanitize=address -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft

PRINTF_DIR = ft_printf

LIBS = -L $(LIBFT_DIR) $(PRINTF_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@make -C $(PRINTF_DIR)
	@cp $(LIBFT_DIR)/libft.a .
	$(CC) $(FLAGS) -lreadline -L ~/.brew/opt/readline/lib $(OBJ) ft_printf/libftprintf.a libft.a -o $@
	@rm libft.a

%.o: %.c $(INC)
	$(CC) $(FLAGS) -I ~/.brew/opt/readline/include -o $@ -c $<

clean:
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)
	rm -f $(OBJ)

fclean: clean
	@make fclean -C $(PRINTF_DIR)
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
