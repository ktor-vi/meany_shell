NAME = minishell


SRC = 	src/main.c \
		src/utils.c \
		src/check_command.c \
		src/echo_command.c \
		src/env_command.c \
		src/cd_command.c \
		src/pwd_command.c

INC = includes/minishell.h

CC = cc

FLAGS =   -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft

LIBS = -L $(LIBFT_DIR) 

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@cp $(LIBFT_DIR)/libft.a .
	$(CC) $(FLAGS) -lreadline $(OBJ) libft.a -o $@ 
	@rm libft.a

%.o: %.c $(INC)
	$(CC) $(FLAGS) -I $(INC) -o $@ -c $<

clean:
	@make fclean -C $(LIBFT_DIR)
	rm -f $(OBJ) 

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
