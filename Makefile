NAME		= nm

CC			= gcc
RM			= rm -f

_SRCS		= main.c

SRCS		= $(addprefix srcs/, $(_SRCS))
OBJS		= $(SRCS:.c=.o)
DEPS		= $(SRCS:.c=.d)

CFLAGS		= -Wall -Wextra -Werror -I.

all:		$(NAME)

%.o : %.c
			$(CC) $(CFLAGS) -c $< -o $@

%.d: %.c
			@set -e; $(RM) $@; \
			$(CC) -M $(CFLAGS) $< > $@.$$$$; \
			sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
			$(RM) $@.$$$$

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS) $(DEPS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

-include $(DEPS)

.PHONY: all clean fclean re
