#include "ft_nm.h"

int print_error(const char *s, const char *prefix)
{
	char *err_str;
	char *tmp;

	err_str = ft_strdup("nm: ");
	if (prefix != NULL) {
		tmp = err_str;
		err_str = ft_strjoin(err_str, prefix);
		free(tmp);
		tmp = err_str;
		err_str = ft_strjoin(err_str, ": ");
		free(tmp);
	}
	tmp = err_str;
	err_str = ft_strjoin(err_str, s);
	free(tmp);
	tmp = err_str;
	err_str = ft_strjoin(err_str, "\n");
	free(tmp);
	ft_putstr_fd(err_str, 2);
	free(err_str);
	return 1;
}
