#include "libft.h"

void ft_putchar_width_fd(char c, size_t width, int fd)
{
	while (width > 0) {
		ft_putchar_fd(c, fd);
		--width;
	}
}
