#include "ft_nm.h"

int nm(const char *ptr, char *path)
{
	char *ei_mag;
	int ei_class;

	ei_mag = ft_substr(ptr, 0, 4);
	if (ft_strcmp(ei_mag, ELFMAG))
		return print_error("File format not recognized", path);
	ei_class = ptr[4];
	if (ei_class == 1)
		(void)42; //
	else if (ei_class == 2)
		parse_64(ptr);
	else
		return print_error("Wrong ei_class", NULL);
	return 0;
}
