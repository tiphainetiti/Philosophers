#################################################
## COLORS
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
END = \033[0m

#################################################
## ARGUMENTS

NAME				= philo
CFLAGS				= -Wall -Werror -Wextra -g3
CC					= cc
BUILD				= objs/

#################################################
## SOURCES

SRC_FILES			= 

OBJ_FILES			= $(addprefix $(BUILD), $(addsuffix .o, ${SRC_FILES}))

#################################################
## RULES

${NAME} : ${OBJ_FILES}
		@${NAME} ${OBJ_FILES}
		@echo "$(GREEN)Compilation terminée! 👍$(END)"

objs/%.o: srcs/%.c
	@mkdir -p ${BUILD}
	@${CC} ${CFLAGS} -c $< -o $@

all : ${NAME}

clean :
		@rm -rf ${BUILD}
		@echo "$(YELLOW)Fichiers objets supprimés.$(END)"

fclean : clean
		@rm -f ${NAME}
		@echo "$(RED)Bibliothèque supprimée.$(END)"

re : fclean all

.PHONY : all clean fclean re