# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 16:08:21 by whendrik          #+#    #+#              #
#    Updated: 2023/12/02 17:32:14 by jhurpy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = @gcc
C_FLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
#S_FLAGS = -g -fsanitize=address,undefined,leak

# Commands
RM = @rm -rf
AR = ar rc

# ---------------------------------------------------------------------------- #

# Target library name and directories
NAME = minishell
LIBFT = ./libft/libft.a
SRC_DIR = src
SRC_FILES = WOLF_PART/main.c \
			WOLF_PART/checker_and_split/lexer.c \
			WOLF_PART/checker_and_split/split_token.c \
			WOLF_PART/identify_and_syntax/token_identify.c\
			WOLF_PART/identify_and_syntax/token_syntax.c\
			WOLF_PART/var_expander/expand_var.c \
			WOLF_PART/var_expander/expander.c \
			WOLF_PART/quote_trimmer/quote_trim.c \
			WOLF_PART/struct_filler/struct_fill.c \
			WOLF_PART/utils/utils_1.c \
			builtins/ft_cd.c \
			builtins/ft_echo.c \
			builtins/ft_env.c \
			builtins/ft_exit.c \
			builtins/ft_export.c \
			builtins/ft_pwd.c \
			builtins/ft_unset.c \
			builtins/utils_builtins.c \
			execution/exec_builtins.c \
			execution/execute_cmd.c \
			execution/fork_process.c \
			execution/separate_op.c \
			message/error_system.c \
			redirection/dup_files.c \
			redirection/here_doc.c \
			redirection/open_infiles.c \
			redirection/open_outfiles.c \
			redirection/redirection.c \
			environment/set_env_jimmy.c \
			environment/free_env.c \
			free_functions.c
			# WOLF_PART/environment/set_env.c 

OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = ./libft
HEAD = -I./includes -I$(READLINE_DIR)include/
INCS = -I$(INC_DIR) -I$(LIBFT_DIR)

# ### INCLUDE ###
LIB 	= -lreadline -L$(READLINE_DIR)lib/
READLINE_DIR = /usr/local/opt/readline/

# Sources, objects and dependencies
SOURCES = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJECTS = $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

# ---------------------------------------------------------------------------- #

# Default target, build the library
all: $(LIBFT_DIR) $(NAME)

# Rule to build each personal library
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Object file build rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) $(HEAD) -c $< -o $@

# Target library build rule
$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(C_FLAGS) $(LIB) $^ $(INCS) -o $(NAME)

# ---------------------------------------------------------------------------- #

# Clean object files
clean:
	$(RM) $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

# Clean object files and target library
fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_DIR)/libft.a
	@make fclean -C $(LIBFT_DIR)

# Clean and rebuild the target library
re: fclean all

# Check code style
norm:
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c ;
	@norminette -R CheckDefine $(INC_DIR)/*.h ;
	@norminette -R CheckForbiddenSourceHeader $(LIBFT_DIR)/src/*.c ;
	@norminette -R CheckDefine $(LIBFT_DIR)/includes/*.h

# Phony targets
.PHONY: all clean fclean re norm