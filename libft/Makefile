SRC_DIR = src
SRCS	= \
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c\
			ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
			ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c\
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
			ft_lstsize.c ft_lstlast.c ft_lstadd_front.c ft_lstadd_back.c\
			ft_lstnew.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c\
			ft_hexatoi.c count_strings.c get_next_line.c get_next_line_utils.c 

OBJ_DIR	= obj
INC_DIR = includes

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3 # -fsanitize=address,undefined,leak
D_FLAGS = -MMD -MP -MF $(OBJ_DIR)/$*.d
RM		= rm -rf
AR		= ar rc
NAME	= libft.a

# Sources and objects
SOURCES = $(addprefix $(SRC_DIR)/, $(SRCS))
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


all:  $(NAME)

# Object file build rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(D_FLAGS) -I $(INC_DIR) -c $< -o $@

# Target library build rule
$(NAME): $(OBJECTS)
	@$(AR) $(NAME) $(OBJECTS)
	@ranlib $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: 	fclean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
	norminette -R CheckDefine $(INC_DIR)/*.h

.PHONY: all clean fclean re norm

