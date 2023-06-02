#include "ft_nm.h"

int print_error(const char *s, const char *prefix)
{
	char *err_str;

	err_str = ft_strdup("nm: ");
	if (prefix != NULL) {
		err_str = ft_strappend(err_str, prefix);
		err_str = ft_strappend(err_str, ": ");
	}
	err_str = ft_strappend(err_str, s);
	err_str = ft_strappend(err_str, "\n");
	ft_putstr_fd(err_str, 2);
	free(err_str);
	return 1;
}
