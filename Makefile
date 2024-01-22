CFILES = get_next_line.c get_next_line_utils.c

BONUS_CFILES = get_next_line_bonus.c get_next_line_utils_bonus.c

OFILES = $(CFILES:.c=.o)

BONUS_OFILES = $(BONUS_CFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = get_next_line.a

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES) 

bonus: $(OFILES) $(BONUS_OFILES)
	ar rcs $(NAME) $(OFILES) $(BONUS_OFILES)

clean:
	rm -f $(OFILES) $(BONUS_OFILES)

fclean:  clean
	rm -f $(NAME)

re: fclean all

.PHONY:  all clean fclean re