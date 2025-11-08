NAME				=	libft.a
CC					=	cc
INC					=	inc/
CFLAGS				=	-Wall -Werror -Wextra -I $(INC)
SRCS				=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))
SRCS_FILES			=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
					ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
					ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
					ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
					ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
					ft_atoi.c ft_calloc.c ft_strdup.c \
					ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
					ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
					ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
					ft_lstnew.c ft_lstadd_front.c \
					ft_lstsize.c ft_lstlast.c \
					ft_lstadd_back.c ft_lstdelone.c \
					ft_lstclear.c ft_lstiter.c ft_lstmap.c \
					$(PRINTF) $(ADD_FUNCT)
ADD_FUNCT			=	ft_free_matrix.c ft_error.c ft_putnbr_base.c \
					ft_str_digit.c get_next_line.c ft_matrix_len.c \
					ft_print_matrix.c ft_realloc.c ft_matrixjoin.c \
					ft_matrixdup.c ft_strcmp.c ft_atoli.c ft_isspace.c
PRINTF				=	printf_utils.c ft_printf.c more_printf_utils.c
SRCS_DIR			=	srcs/

OBJS				=	$(addprefix $(OBJS_DIR), $(OBJS_FILES))
OBJS_FILES			=	$(SRCS_FILES:%.c=%.o)
OBJS_DIR			=	objs/

# Colors

BOLD_PURPLE	=	\033[1;35m
BOLD_CYAN	=	\033[1;36m
BOLD_YELLOW	=	\033[1;33m
NO_COLOR	=	\033[0m
DEF_COLOR 	=	\033[0;39m
GRAY 		=	\033[0;90m
RED 		=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW 		=	\033[0;93m
BLUE 		=	\033[0;94m
MAGENTA 	=	\033[0;95m
CYAN 		=	\033[0;96m
WHITE		=	\033[0;97m

all:	$(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	echo "$(GREEN)\nlibft.a compiled!$(DEF_COLOR)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	[ -d $(OBJS_DIR) ] | mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	printf "\33[2K\r$(GRAY)$(CC) $(CFLAGS) -c $< -o $@$(DEF_COLOR)"

clean:
	rm -rf $(OBJS_DIR)
	find . -name "*.swap" -delete
	find . -name ".DS_Store" -delete
	echo "\nlibft$(YELLOW) cleaned$(DEF_COLOR)"

fclean: clean
	rm -f $(NAME)

re: fclean all

.SILENT: all $(NAME) re clean fclean $(OBJS) $(OBJS_DIR)
.PHONY: all bonus clean fclean re
