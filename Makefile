FILES				= utils base64 url

NAME				= cyberlib.a

CC					= gcc
CCFLAGS				= -Wall -Wextra -Werror -D_FORTIFY_SOURCE=3 -O2 -fstack-protector-strong -fstack-clash-protection
MAKEFLAGS			= --no-print-directory
AR					= ar rcs
RM					= rm -rf

FILES_PATH			= src/

OBJ_DIR				= .obj/

SRCS				= $(addprefix $(FILES_PATH), $(addsuffix .c, $(FILES)))
OBJS				= $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))

vpath %.c $(FILES_PATH)

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^
	@echo "$(GREEN)-== $(NAME) created! ==-$(DEFAULT)"

$(OBJ_DIR)%.o: %.c
	@echo "Compiling $< to $@"
	@$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

check-norm: all
	@norminette src/ lib/libft inc/ | grep -B 1 "Error\|Warning" || echo "$(GREEN)Norme check passed!$(DEFAULT)"
	
clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)-== all object files deleted! ==-$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)-== all files deleted! ==-$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re

# ANSI COLOR CODES
DEFAULT = \033[0m
RED     = \033[1;31m
YELLOW  = \033[1;33m
GREEN   = \033[1;32m
BLUE    = \033[1;36m
ORANGE  = \033[38;5;208m