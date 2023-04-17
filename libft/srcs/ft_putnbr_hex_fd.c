#include "libft.h"

void ft_putnbr_hex_fd(long long n, int fd, size_t width)
{
	char *digits = "0123456789abcdef";
	char d;

	if (n < 0) {
		write(fd, "-", 1);
		ft_putnbr_hex_fd(-n, fd, width - 1);
	} else {
		d = digits[n % 16];
		if (width > 1)
			ft_putnbr_hex_fd(n / 16, fd, width - 1);
		write(fd, &d, 1);
	}
}
