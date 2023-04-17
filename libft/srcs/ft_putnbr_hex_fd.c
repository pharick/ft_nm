#include "libft.h"

void ft_putnbr_hex_fd(long long n, size_t width, int fd)
{
	char *digits = "0123456789abcdef";
	char d;

	if (n < 0) {
		write(fd, "-", 1);
		ft_putnbr_hex_fd(-n, width - 1, fd);
	} else {
		d = digits[n % 16];
		if (width > 1)
			ft_putnbr_hex_fd(n / 16, width - 1, fd);
		write(fd, &d, 1);
	}
}
