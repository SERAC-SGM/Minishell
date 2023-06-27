#______________________________________________________________________________#
############################### Target Names ###################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

# Name
NAME	= ./minishell
PROJECT_NAME = Minishell

#______________________________________________________________________________#
############################### Compiler #######################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

# Compiler
CC = cc 

# Compiler Flags
CFLAGS = -Wall -Wextra -Werror -g

ifeq ($(debug), 1)
	CFLAGS += -g
endif

#______________________________________________________________________________#
############################### Libraries ######################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

# Libft
LIB_DIR		= ./libft
LIBFT		= $(LIB_DIR)/libft.a
LDFLAGS 	= -L $(LIB_DIR) -lft -lreadline

#______________________________________________________________________________#
############################### Print Variables ################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

# Reset
NC = \033[0m

# Colors
YELLOW = \033[0;33m
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
PURPLE = \033[0;35m
CYAN = \033[0;36m
BLACK = \033[0;30
WHITE = \033[0;37m

# Colors
BYELLOW = \033[1;33m
BGREEN = \033[1;32m
BBLUE = \033[1;34m
BRED = \033[1;31m
BPURPLE = \033[1;35m
BCYAN = \033[1;36m
BBLACK = \033[1;30m
BWHITE = \033[1;37m

# One Line Output
OL =\e[1A\r\033[K
CLEAR = \033[2K

#______________________________________________________________________________#
############################### Includes #######################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

INC_DIR = ./inc
INCLUDES += -I $(INC_DIR)
INCLUDES += -I $(LIB_DIR)/inc

#______________________________________________________________________________#
############################### Headers ########################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

HEADER += mshell_types.h
HEADER += core.h
HEADER += lexer.h
HEADER += expander.h
HEADER += parser.h
HEADER += executor.h
HEADER += builtins.h
HEADER += minishell.h

vpath %.h $(INC_DIR)

#______________________________________________________________________________#
############################### Path Sources ###################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

SRCS_DIR = ./srcs
#Core Main directory
PATH_SRCS_CORE = $(SRCS_DIR)/00_core
#Core Sub-directories
PATH_SRCS_INIT = $(SRCS_DIR)/00_core/01_init
PATH_SRCS_ENV = $(SRCS_DIR)/00_core/02_environment
PATH_SRCS_SIG = $(SRCS_DIR)/00_core/03_signals
PATH_SRCS_ERR = $(SRCS_DIR)/00_core/04_error
PATH_SRCS_FREE = $(SRCS_DIR)/00_core/05_free
PATH_SRCS_UTIL = $(SRCS_DIR)/00_core/06_utils
#Lexer directory
PATH_SRCS_LEXER = $(SRCS_DIR)/10_lexer
#Expander directory
PATH_SRCS_EXPAND = $(SRCS_DIR)/20_expander
#Parser directory
PATH_SRCS_PARSER = $(SRCS_DIR)/30_parser
#Executor directory
PATH_SRCS_EXEC = $(SRCS_DIR)/40_executor
#Builtins directory
PATH_SRCS_BUILTIN = $(SRCS_DIR)/50_builtins

#______________________________________________________________________________#
############################### Sources ########################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

#00_core
SRCS += minishell.c

#01_init
SRCS += init_ft.c

#02_environment
SRCS += env_ft.c

#03_signals
SRCS += signal_actions.c
SRCS += signal.c

#04_error
SRCS += error_manager.c

#05_free
SRCS += free_ft.c

#06_utils
SRCS += util_ft.c
SRCS += list_ft.c
SRCS += list_ft2.c

#10_lexer
SRCS += lexer_util.c
SRCS += input_mode.c
SRCS += token_lst.c
SRCS += token.c
SRCS += lexer_error.c
SRCS += lexer.c

#20_expander
SRCS += expander.c

#30_parser
SRCS += parsing_error.c
SRCS += redirection.c
SRCS += parser.c

#40_executor
SRCS += pipe_dup.c
SRCS += files_manager.c
SRCS += here_doc.c
SRCS += exec_native.c
SRCS += exec_builtin.c
SRCS += exec.c

#50_buildins
SRCS += cd.c
SRCS += echo.c
SRCS += env.c
SRCS += pwd.c
SRCS += export.c
SRCS += unset.c
SRCS += exit.c


#______________________________________________________________________________#
############################### Attribution ####################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

vpath %.c $(PATH_SRCS_CORE)
vpath %.c $(PATH_SRCS_INIT)
vpath %.c $(PATH_SRCS_ENV)
vpath %.c $(PATH_SRCS_SIG)
vpath %.c $(PATH_SRCS_ERR)
vpath %.c $(PATH_SRCS_FREE)
vpath %.c $(PATH_SRCS_UTIL)
vpath %.c $(PATH_SRCS_LEXER)
vpath %.c $(PATH_SRCS_PARSER)
vpath %.c $(PATH_SRCS_EXPAND)
vpath %.c $(PATH_SRCS_EXEC)
vpath %.c $(PATH_SRCS_BUILTIN)

#______________________________________________________________________________#
############################### Objects ########################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

OBJS_DIR = ./objs
OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))
CHK_OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(CHK_SRCS))

#______________________________________________________________________________#
############################### Dependencies ###################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

DEPS_DIR = ./build
DEPS = $(addprefix $(DEPS_DIR)/, $(notdir $(OBJS:.o=.d)))

#______________________________________________________________________________#
############################### Progress Bar ###################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

# PROGRESS BAR
NB_OBJ = ${words ${OBJS}}
COUNTER = 1
PROGRESS = 0
DONE = 100
SPACE = 0
FILL = 0
EMPTY = 0

define PROGRESS_BAR
	$(eval PROGRESS=$(shell echo $$(($(COUNTER) * 100 / $(NB_OBJ)))))
	$(eval DONE=$(shell echo $$(($(PROGRESS) * 30 / 100))))
	$(eval SPACE=$(shell echo $$((30 - $(DONE)))))
	$(eval FILL=$(shell printf "%*s" ${DONE} | sed 's/ /◼/g'))
	$(eval EMPTY=$(shell printf "%*s" ${SPACE} | sed 's/ /◼/g'))
	printf "\r${CLEAR}$(BCYAN)Compile : $(GREEN)${FILL}$(RED)${EMPTY} $(BWHITE)%3d%%$(END) $(CYAN)%s.c " ${PROGRESS} $1
	$(eval COUNTER=$(shell echo $$(($(COUNTER) + 1))))
endef

#______________________________________________________________________________#
############################### Rules ##########################################
#‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾#

#_____Build_____#
all: $(LIBFT) $(NAME)
	@echo "--▶ $(BGREEN)all\t$(GREEN)done$(NC)"
	@echo "--------------------------------------------------"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) $(INCLUDES) -o $@
    #-----Output-----#
	@echo "$(WHITE)\n▶$(BGREEN)$(NAME)\t$(GREEN)Executable created$(NC)"

$(OBJS): $(OBJS_DIR)/%.o: %.c | $(LIBFT) dir where
	@$(CC) $(CFLAGS) -MMD $(INCLUDES) -c $< -o $@
	@mv $(basename $@).d $(DEPS_DIR)/$(notdir $(basename $@)).d
    #-----Output-----#
	@$(call PROGRESS_BAR, $(basename $(notdir $<)))

# Libraries
$(LIBFT):
	@make --no-print-directory all -C $(LIB_DIR)

-include $(DEPS)

# Directories
dir: $(OBJS_DIR) $(DEPS_DIR)

$(OBJS_DIR):
	@mkdir $@

$(DEPS_DIR):
	@mkdir $@

bonus: all

#_____Clean_____#
clean: lclean where_c
	@rm -rf $(OBJS_DIR)
	@rm -rf $(DEPS_DIR)
    #-----Output-----#
	@echo "▶ $(BYELLOW)clean $(YELLOW)Object files removed from $(PROJECT_NAME)$(NC)"
	@echo "▶ \t$(YELLOW)Dependencies files removed from $(PROJECT_NAME)$(NC)"
	@echo "--▶ $(BYELLOW)clean$(YELLOW) done$(NC)"

# Libraries Clean
lclean:
	@make --no-print-directory clean -C $(LIB_DIR)

fclean: clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)
    #-----Output-----#
	@echo "▶ $(BRED)fclean $(RED)libft.a removed$(NC)"
	@echo "\t$(RED)$(NAME) removed$(NC)"
	@echo "--▶ $(BRED)fclean$(RED) done$(NC)"

# Current Make
where_c:
	@echo "$(BBLACK)>$(PROJECT_NAME)$(NC)"

where:
	@echo "$(BBLACK)>$(PROJECT_NAME)$(NC)"

re: fclean all

.PHONY: all clean fclean re
