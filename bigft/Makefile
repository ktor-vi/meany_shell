#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := libft.a
CC        := cc
FLAGS    := -g -Wall -Wextra -Werror 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=            ft_printf/ft_printf.c \
                          ft_printf/ft_printf_handle_1.c \
                          ft_printf/ft_printf_handle_2.c \
                          ft_printf/ft_printf_utils.c \
                          ft_printf/ft_printf_utils_2.c \
                          get_next_line/get_next_line.c \
                          get_next_line/get_next_line_utils.c \
                          libft/ft_atoi.c \
                          libft/ft_bzero.c \
                          libft/ft_calloc.c \
                          libft/ft_isalnum.c \
                          libft/ft_isalpha.c \
                          libft/ft_isascii.c \
                          libft/ft_isdigit.c \
                          libft/ft_isprint.c \
                          libft/ft_itoa.c \
                          libft/ft_lstadd_back_bonus.c \
                          libft/ft_lstadd_front_bonus.c \
                          libft/ft_lstclear_bonus.c \
                          libft/ft_lstdelone_bonus.c \
                          libft/ft_lstiter_bonus.c \
                          libft/ft_lstlast_bonus.c \
                          libft/ft_lstmap_bonus.c \
                          libft/ft_lstnew_bonus.c \
                          libft/ft_lstsize_bonus.c \
                          libft/ft_memcmp.c \
                          libft/ft_memcpy.c \
                          libft/ft_memmove.c \
                          libft/ft_memset.c \
                          libft/ft_putchar_fd.c \
                          libft/ft_putendl_fd.c \
                          libft/ft_putnbr_fd.c \
                          libft/ft_putstr_fd.c \
                          libft/ft_split.c \
                          libft/ft_strchr.c \
                          libft/ft_strdup.c \
                          libft/ft_striteri.c \
                          libft/ft_strjoin.c \
                          libft/ft_strlcat.c \
                          libft/ft_strlcpy.c \
                          libft/ft_strlen.c \
                          libft/ft_strmapi.c \
                          libft/ft_strcmp.c \
                          libft/ft_strncmp.c \
                          libft/ft_strnstr.c \
                          libft/ft_strrchr.c \
                          libft/ft_strtrim.c \
                          libft/ft_substr.c \
                          libft/ft_tolower.c \
                          libft/ft_toupper.c \
                          
OBJS        := $(SRCS:.c=.o)

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

total_files := $(words $(SRCS))
current_file := 0
progress := 0

define progress_bar
@$(eval current_file=$(shell echo $$(($(current_file) + 1))))
@$(eval progress=$(shell echo $$(($(current_file) * 100 / $(total_files)))))
@printf "\r$(GREEN)Compiling $(YELLOW)bigft$(CLR_RMV)... [%-3d%%] %d/%d $(CYAN)"  $(progress) $(current_file) $(total_files)
endef

define print_completion
@printf "$(GREEN)Compilation of $(YELLOW)$(NAME) $(GREEN)complete ✔️$(CLR_RMV)"
endef

all:	nothing                   ${NAME}

re:			fclean all

%.o: %.c $(DEPS)
	@$(CC) $(FLAGS) -c $< -o $@
	@$(call progress_bar)

clean:
			@ ${RM} *.o */*.o */*/*.o

fclean:		clean
			@ ${RM} ${NAME}
${NAME}:	$(OBJS)
	                                                    @echo "$(YELLOW)Done!$(CLR_RMV)"
	                                                    @ar rcs $(NAME) $(OBJS)
			@echo "$(GREEN)$(NAME) created ✔️"
nothing:
	@if [ -f "$(NAME)" ] && [ -z "$$(find $(SRCS) -newer $(NAME))" ]; then \
	                          echo "\r$(CYAN)bigft is up to date$(CLR_RMV)"; \
                          fi 
.PHONY:		all clean fclean re nothing


