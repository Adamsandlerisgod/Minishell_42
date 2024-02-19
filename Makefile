# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 16:08:21 by whendrik          #+#    #+#              #
#    Updated: 2024/01/23 20:11:06 by whendrik         ###   ########.fr        #
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
SRC_FILES = main.c \
			builtins/ft_cd.c \
			builtins/ft_echo.c \
			builtins/ft_env.c \
			builtins/ft_exit.c \
			builtins/ft_export.c \
			builtins/ft_pwd.c \
			builtins/ft_unset.c \
			environment/set_env.c \
			environment/free_env.c \
			execution/exec_builtins.c \
			execution/fork_process.c \
			execution/child_process.c \
			execution/separate_op.c \
			message/error_system.c \
			message/error_cmd.c \
			parser_lexer/assign_path.c \
			parser_lexer/check_line.c \
			parser_lexer/identify_cmd.c \
			parser_lexer/quote_trim.c \
			parser_lexer/split_tokens.c \
			parser_lexer/token_identify.c\
			parser_lexer/token_syntax.c\
			parser_lexer/variable_parser.c \
			redirection/assign_fd.c \
			redirection/here_doc.c \
			signal/signal.c \
			signal/signal_child.c \
			signal/exit_status.c \
			utils/free_functions.c \
			utils/initialization.c \
			utils/utils_builtins.c \
			utils/utils_token.c \
			utils/utils_var.c

OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = ./libft
HEAD = -I./includes -I$(READLINE_DIR)include/
INCS = -I$(INC_DIR) -I$(LIBFT_DIR)
HDRS = $(INC_DIR)/minishell.h

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
	make -C $(LIBFT_DIR)

# Object file build rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT) $(HDRS) Makefile
	mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) $(HEAD) -c $< -o $@

# Target library build rule
$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(C_FLAGS) $(LIB) $^ $(INCS) -o $(NAME)

# ---------------------------------------------------------------------------- #

# Phony targets
.PHONY: all clean fclean re norm

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
	@norminette $(SRC_DIR)
	@norminette $(INC_DIR)
	@norminette $(LIBFT_DIR)
