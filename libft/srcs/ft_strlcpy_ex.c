#include "libft.h"

size_t ft_strlcpy_ex(char *dst, const char *src, size_t dstsize, char *ignore,
		     int lowercase)
{
	size_t i;

	i = 0;
	if (dst == NULL || src == NULL)
		return 0;
	if (dstsize == 0)
		return ft_strlen(src);
	while (*src && (i < dstsize - 1)) {
		if (!ignore || !ft_strchr(ignore, *src)) {
			*dst = *src;
			if (lowercase && *dst >= 'A' && *dst <= 'Z')
				*dst += 32;
			++dst;
		}
		++src;
		i++;
	}
	while (*src) {
		i++;
		src++;
	}
	if (dstsize > 0)
		*dst = '\0';
	return i;
}
