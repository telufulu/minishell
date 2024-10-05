NAME			=		minishell
CC				=		cc
CFLAGS			=		-Wall -Werror -Wextra -I$(INC) -I$(LIBFT_DIR)inc/
SANITIZE		=		-fsanitize=
INC				=		inc/

SRCS_DIR		=		srcs/
OBJS_DIR		=		objs/

SRCS			=		$(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS			=		$(addprefix $(OBJS_DIR), $(OBJS_FILES))
OBJS_FILES		=		$(SRCS_FILES:%.c=%.o)
SRCS_FILES		=		main.c utils.c env.c signals.c
SRCS_FILES		+=		parser/parser.c parser/parser_args.c \
						parser/parser_utils.c parser/parser_variable.c
#SRCS_FILES		+=		lexer/lexer_main.c
#SRCS_FILES		+=		executor/executor_main.c

LIBS			=		libs/
LIBFT			=		$(LIBFT_DIR)libft.a
LIBFT_DIR		=		$(LIBS)libft/

LFLAGS			=		-L $(LIBFT_DIR) -lft -lreadline

## Colors

BOLD_PURPLE		=		\033[1;35m
BOLD_CYAN		=		\033[1;36m
BOLD_YELLOW		=		\033[1;33m
NO_COLOR		=		\033[0m
DEF_COLOR		=		\033[0;39m
GRAY			=		\033[0;90m
RED				=		\033[0;91m
GREEN			=		\033[0;92m
YELLOW			=		\033[0;93m
BLUE			=		\033[0;94m
MAGENTA			=		\033[0;95m
CYAN			=		\033[0;96m
WHITE			=		\033[0;97m

all:	$(NAME)

sanitize:				CFLAGS += $(SANITIZE) -g3
sanitize:				clean all

sanitize_leaks:			CFLAGS += $(SANITIZE)address -g3
sanitize_leaks:			clean all

sanitize_threads:		CFLAGS += $(SANITIZE)thread -pthread
sanitize_threads:		clean all

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	echo "$(BLUE)\n------------\n| Done! 👌 |\n------------\$(DEF_COLOR)"

$(LIBFT):
	make -C $(LIBFT_DIR) --no-print-directory

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
	if [ ! -d $(OBJS_DIR) ]; then echo "\nCompiling $(BLUE)$(NAME)$(DEF_COLOR)"; fi
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)lexer
	mkdir -p $(OBJS_DIR)parser
	mkdir -p $(OBJS_DIR)executor
	$(CC) $(CFLAGS) -c $< -o $@
	echo  "\33[2K\r$(GRAY)$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@$(DEF_COLOR)"

clean:
	echo "\nCleaning$(BLUE)...$(DEF_COLOR)"
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR) --no-print-directory
	find . -name "*.swap" -delete
	find . -name ".DS_Store" -delete
	find . -name "*.gch" -delete
	find . -name "*._." -delete
	echo "$(BLUE)\n------------\n|  clean   |\n| Done! 👌 |\n------------$(DEF_COLOR)"

fclean:	clean
	make fclean -C $(LIBFT_DIR) --no-print-directory
	rm -f $(NAME)

re:		fclean all

.SILENT: all clean fclean re $(NAME) $(LIBFT) $(OBJS)
.PHONY: all clean fclean re
