#################################################
## COLORS
BLACK   = \033[0;30m
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
WHITE   = \033[0;37m
END     = \033[0m

################################################# 
## ARGUMENTS

NAME    = philo
CC      = cc
CFLAGS  = -Wall -Werror -Wextra -pthread -g3
BUILD   = objs/
INCLUDE = includes/

#################################################
## SOURCES

SRC_FILES = main \
			init \
			routine \
			utils \
			check \
			monitor \
			parsing \
			cleaning

SRC       = $(addprefix srcs/, $(addsuffix .c, $(SRC_FILES)))
OBJ_FILES = $(patsubst srcs/%.c, $(BUILD)%.o, $(SRC))

#################################################
## RULES

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)
	@echo "$(GREEN)Compilation done!$(END)"

$(BUILD)%.o: srcs/%.c
	@mkdir -p $(BUILD)
	@echo "$(YELLOW)Compilation of $*..$(END)"
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(BUILD)
	@echo "$(CYAN)Cleaning intermediate files.$(END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)All clean!$(END)"

re: fclean all

.PHONY: all clean fclean re
