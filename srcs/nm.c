#include "ft_nm.h"

int nm(char *ptr, char *path)
{
	char *mag;

	mag = ft_substr(ptr, 0, 4);
	if (ft_strcmp(mag, ELFMAG))
		return print_error("File format not recognized", path);

	return 0;
}
