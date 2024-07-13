NAME = minishell
BONUS = meanyshell

SRC =  src/main.c                   \
	src/signals.c	          		\
                                    \
	src/build_envs.c                \
	src/lexer.c                     \
	src/lexer_handlers.c	      	\
	src/lexer_utils.c		        \
	src/expand.c                    \
	src/expand_utils.c				\
	src/quotes.c                    \
	src/populate.c                  \
	src/populate_helpers.c          \
									\
	src/post-parse.c                \
                                    \
	src/piping.c                    \
		                            \
	src/heredoc.c                 	\
	src/envs_commands.c             \
	src/export_unset.c              \
	src/check_command.c             \
	src/cd_command.c                \
	src/pwd_command.c               \
	src/echo_command.c              \
                                    \
	src/env_utils.c                 \
	src/env_mem.c                   \
	src/tok_utils.c                 \
	src/quotes_utils.c              \
	src/cmd_utils.c                 \
	src/exec_utils.c                \
	src/exec_helpers.c              \
	src/exp_uns_utils.c             \
	src/misc_utils.c                \
	src/misc_utils2.c				\
	                                \
	src/exec_errors.c               \
	src/syntax_errors.c             \
	src/clean.c


INC = -I includes  -I/opt/homebrew/opt/readline/include
CC = cc

FLAGS = -g -Wall -Wextra -Werror -arch arm64 -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3
LIBFT_LIBRARY_DIR = bigft  # Descriptive variable name

LIBS =   bigft/libft.a -lreadline -L/opt/homebrew/opt/readline/lib

OBJS := $(patsubst src/%.c, objs/%.o, ${SRC})
BONUS_OBJS := $(BONUS_SRCS:.c=.o)

DEPS := $(INC) 

GREEN := \033[1;32m
YELLOW := \033[1;33m
CYAN := \033[1;36m
CLR_RMV := \033[0m
RED		:= \033[1;31m

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



.PHONY: all clean fclean nothing nothingb bonus re

all: nothing $(NAME)

bonus: nothing $(BONUS)

re: fclean all

objs/%.o:    src/%.c
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<
	@$(call progress_bar)


clean:
	@make clean -C $(LIBFT_LIBRARY_DIR)
	@ echo "$(GREEN)Deleting $(YELLOW)bigft $(CLR_RMV)objs ✔️"
	@rm -rf $(OBJS)
	@echo "$(GREEN)Deleting $(YELLOW)$(NAME)$(CLR_RMV) objs ✔️"

fclean: clean
	@make fclean -C $(LIBFT_LIBRARY_DIR)
	@ echo "$(GREEN)Deleting $(YELLOW)bigft $(CLR_RMV)binary ✔️"
	@rm -rf $(NAME)
	@echo "$(GREEN)Deleting $(YELLOW)$(NAME)$(CLR_RMV) binary ✔️"

$(NAME): $(OBJS)
	@echo "$(YELLOW)Done!$(CLR_RMV)"
	@make  -C $(LIBFT_LIBRARY_DIR)
	@$(CC) $(FLAGS) $(OBJS) $(LIBS) -o $@
	@$(call print_completion)

nothing:
	@mkdir -p objs
	@if [ -f "$(NAME)" ] && [ -z "$$(find $(SRC) -newer $(NAME))" ]; then \
		echo "$(CYAN)Nothing has been updated.$(CLR_RMV)"; \
		fi
.PHONY: all re clean fclean nothing nothingb bonus

