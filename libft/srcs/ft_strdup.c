#include "libft.h"

char *ft_strdup(const char *s1)
{
	char *s2;
	size_t len;

	len = ft_strlen(s1);
	s2 = (char *)malloc((len + 1) * sizeof(char));
	if (!s2) {
		errno = ENOMEM;
		return (NULL);
	}
	ft_strlcpy(s2, s1, len + 1);
	return (s2);
}
