NAME		= libft.a

CC		= gcc
AR		= ar rc
RM		= rm -f

_SRCS		= ft_strlen.c ft_strlcat.c ft_strlcopy.c ft_strjoin.c \
		  ft_substr.c ft_strdup.c ft_strcmp.c ft_putchar_fd.c \
		  ft_putstr_fd.c ft_strappend.c ft_lstnew.c ft_lstadd_front.c \
		  ft_lstiter.c ft_putnbr_hex_fd.c ft_lstsize.c ft_strlower.c

SRCS		= $(addprefix srcs/, $(_SRCS))
OBJS		= $(SRCS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror
DEPS		= $(SRCS:.c=.d)

all:		$(NAME)

%.o : %.c
		$(CC) $(CFLAGS) -I. -c $< -o $@

%.d: %.c
		@set -e; $(RM) $@; \
		$(CC) -M $(CFLAGS) -I. $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		$(RM) $@.$$$$

$(NAME):	$(OBJS)
		$(AR) $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS) $(DEPS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

-include $(DEPS)

.PHONY: all clean fclean re
