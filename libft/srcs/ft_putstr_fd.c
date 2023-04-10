#include "libft.h"

void ft_putstr_fd(const char *s, int fd)
{
	if (s == NULL)
		return;
	while (*s)
		ft_putchar_fd(*(s++), fd);
}
