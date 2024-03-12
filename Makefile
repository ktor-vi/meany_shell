NAME = minishell
BONUS = meanyshell

SRC =  src/main.c \
       src/utils.c \
       src/check_command.c \
       src/echo_command.c \
       src/envs_commands.c \
       src/build_envs.c \
       src/export_unset.c \
       src/env_utils.c \
       src/env_mem.c \
       src/exec_utils.c \
       src/exec_helpers.c \
       src/cd_command.c \
       src/pwd_command.c \
       src/populate.c \
       src/lexer.c \
       src/piping.c


INC = includes/minishell.h

CC = gcc -w

FLAGS = -g -fsanitize=address \
        -lreadline -L ~/.brew/opt/readline/lib  \
        -I/Users/vphilipp/.brew/opt/readline/include

LIBFT_LIBRARY_DIR = bigft/  # Descriptive variable name

LIBS = -L $(LIBFT_LIBRARY_DIR) -L/Users/vphilipp/.brew/opt/readline/lib

OBJS := $(patsubst src/%.c, objs/%.o, ${SRC})
BONUS_OBJS := $(BONUS_SRCS:.c=.o)

DEPS := $(INC) 
# Color codes for terminal output (use with caution)
GREEN := \033[1;32m
YELLOW := \033[1;33m
CYAN := \033[1;36m
CLR_RMV := \033[0m

total_files := $(words $(SRC))
current_file := 0
progress := 0

define progress_bar
@$(eval current_file=$(shell echo $$(($(current_file) + 1))))
@$(eval progress=$(shell echo $$(($(current_file) * 100 / $(total_files)))))
@printf "\r$(GREEN)Compiling $(YELLOW)%s$(CLR_RMV)... [%-3d%%] %d/%d $(CYAN)" $< $(progress) $(current_file) $(total_files)
endef

define print_completion
@printf "\n$(GREEN)Compilation of $(YELLOW)$(NAME) $(GREEN)complete ✔️\n$(CLR_RMV)"
endef

define print_completionb
@printf "\n$(GREEN)Compilation of $(YELLOW)$(BONUS) $(GREEN)complete ✔️\n$(CLR_RMV)"
endef

define print_completionl
@printf "$(GREEN)Compilation of $(YELLOW)libft.a $(GREEN)complete ✔️\n$(CLR_RMV)"
endef

define print_completionp
@printf "\n$(GREEN)Compilation of $(YELLOW)libftprintf.a $(GREEN)complete ✔️\n$(CLR_RMV)"
endef

.PHONY: all clean fclean nothing nothingb bonus re

all: nothing $(NAME)

bonus: nothing $(BONUS)

re: fclean all

objs/%.o: src/%.c $(DEPS)
	@$(CC) $(FLAGS) -c $< -o $@
	$(call progress_bar)


clean:
	@make clean -C $(LIBFT_LIBRARY_DIR)
	@rm -rf $(OBJS)
	@echo "$(GREEN)Deleting $(YELLOW)$(NAME)$(CLR_RMV) objects ✔️"
	@if [ -f "$(BONUS)" ] && [ -z "$(find $(BONUS_OBJS) -newer $(BONUS))" ]; then \
		echo "$(GREEN)Deleting $(YELLOW)$(BONUS_OBJS)$(CLR_RMV) objects ✔️"; \
		rm -rf $(BONUS_OBJS); fi

fclean: clean
	@make fclean -C $(LIBFT_LIBRARY_DIR)
	@rm -rf $(NAME)
	@echo "$(GREEN)Deleting $(YELLOW)$(NAME)$(CLR_RMV) binary ✔️"

# Targets for building libft and minishell
# Target for building main minishell executable
$(NAME): $(LIBFT_LIBRARY_DIR) $(OBJS)
	@echo "$(YELLOW)Done!$(CLR_RMV)"
	@make  -C $(LIBFT_LIBRARY_DIR)
	@$(CC) $(FLAGS) $(OBJS) bigft/libft.a -o $@
	@$(call print_completion)

# Target for building "meanyshell" (adjust source files as needed)
$(BONUS): $(BONUS_OBJS)
	@echo "$(YELLOW)Done!$(CLR_RMV)"
	@make -C $(LIBFT_LIBRARY_DIR)  # Remove extra space
	@$(CC) $(FLAGS) $(BONUS_OBJS) -o $@
	@$(call print_completionb)

$(LIBFT_LIBRARY_DIR):
	@echo "$(YELLOW)Building libft...$(CLR_RMV)"$(LIBFT_LIBRARY_DIR):  # Implicit dependency for libft build
	@echo "$(YELLOW)Building libft...$(CLR_RMV)"

nothing:
	@if [ -f "$(NAME)" ] && [ -z "$$(find $(SRC) -newer $(NAME))" ]; then \
		echo "$(CYAN)Nothing has been updated.$(CLR_RMV)"; \
	fi
.PHONY: all re clean fclean nothing nothingb bonus
