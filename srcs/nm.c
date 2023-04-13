#include "ft_nm.h"

void print_sym(struct s_symbol *sym)
{
	printf("%x %s\n", sym->st_value, sym->st_name);
}

int nm(const char *ptr, char *path)
{
	char *ei_mag;
	int ei_class;
	t_list *sym_list;

	ei_mag = ft_substr(ptr, 0, 4);
	if (ft_strcmp(ei_mag, ELFMAG))
		return print_error("File format not recognized", path);
	ei_class = ptr[4];
	if (ei_class == 1)
		sym_list = parse_32(ptr);
	else if (ei_class == 2)
		sym_list = parse_64(ptr);
	else
		return print_error("Wrong ei_class", NULL);
	ft_lstiter(sym_list, (void (*)(void *))print_sym);
	return 0;
}
