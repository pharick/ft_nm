NAME		= nm

CC		= gcc
RM		= rm -f

_SRCS		= main.c nm.c parse_elf.c errors.c

SRCS		= $(addprefix srcs/, $(_SRCS))
OBJS		= $(SRCS:.c=.o)
DEPS		= $(SRCS:.c=.d)

CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME)

%.o : %.c
		$(CC) $(CFLAGS) -I. -Ilibft -c $< -o $@

%.d: %.c
		@set -e; $(RM) $@; \
		$(CC) -M $(CFLAGS) -I. -Ilibft $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		$(RM) $@.$$$$

$(NAME):	$(OBJS)
		make -C libft
		$(CC) $(OBJS) -o $(NAME) -Llibft -lft

clean:
		$(RM) $(OBJS) $(DEPS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

-include $(DEPS)

.PHONY: all clean fclean re
