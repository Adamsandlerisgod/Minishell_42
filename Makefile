# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 02:03:42 by jhurpy            #+#    #+#              #
#    Updated: 2023/10/09 16:06:19 by jhurpy           ###   ########.fr        #
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
SRC_FILES =	environment/free_env.c \
			environment/set_env.c \
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

OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = ./libft
INCS = -I$(INC_DIR) -I$(LIBFT_DIR)

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
	$(CC) $(C_FLAGS) -c $< -o $@

# Target library build rule
$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(C_FLAGS) $^ $(INCS) -o $(NAME)

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
