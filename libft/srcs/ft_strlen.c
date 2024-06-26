#include "libft.h"

size_t ft_strlen(const char *s)
{
	int len;

	if (s == NULL)
		return 0;
	len = 0;
	while (s[len] != '\0')
		++len;
	return len;
}
