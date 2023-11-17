# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 01:19:33 by jhurpy            #+#    #+#              #
#    Updated: 2023/11/15 20:47:34 by whendrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = gcc
C_FLAGS = -Wall -Wextra -Werror -g3 # -fsanitize=address,undefined,leak
D_FLAGS = -MMD -MP -MF $(OBJ_DIR)/$*.d

RM = rm -rf
AR = ar rc

# Target library name and directories
NAME = libft.a
SRC_DIR = src
SRC_FILES = ft_atoi.c \
		ft_atol.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_hexatoi.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_ishexa.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_realloc.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line.c \
		get_next_line_utils.c\
		ft_isquote.c

OBJ_DIR = obj
INC_DIR = includes

# Sources and objects
SOURCES = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target, build the library
all: $(NAME)

# Object file build rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(D_FLAGS) -I $(INC_DIR) -c $< -o $@

# Target library build rule
$(NAME): $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS)
	@ranlib $(NAME) 

# Clean object files
clean:
	$(RM) $(OBJ_DIR)

# Clean object files and target library
fclean: clean
	$(RM) $(NAME)

# Clean and rebuild the target library
re: fclean all

# Check code style
norm:
	norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
	norminette -R CheckDefine $(INC_DIR)/*.h

# Phony targets
.PHONY: all clean fclean re norm
