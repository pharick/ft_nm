#include "ft_nm.h"

static void print_sym(struct s_symbol *sym)
{
	// printf("%x --- %s %lu\n", sym->st_shndx, sym->sh_name,
	//        sym->sh_flags & SHF_WRITE);
	ft_putnbr_hex_fd(sym->st_value, 1,
			 sym->ei_class == ELFCLASS32 ? 8 : 16);
	ft_putchar_fd(' ', 1);
	ft_putchar_fd(get_sym_type(sym), 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(sym->st_name, 1);
	ft_putchar_fd('\n', 1);
}

static int sym_name_comp(char *n1, char *n2)
{
	char *n1_low;
	char *n2_low;
	int res;

	while (*n1 == '_')
		++n1;
	while (*n2 == '_')
		++n2;
	n1_low = ft_strdup(n1);
	n2_low = ft_strdup(n2);
	ft_strlower(n1_low);
	ft_strlower(n2_low);
	res = ft_strcmp(n1_low, n2_low);
	free(n1_low);
	free(n2_low);
	return res;
}

static void sort_sym_list(t_list *sym_list)
{
	t_list *current;
	void *tmp;
	size_t size;

	size = ft_lstsize(sym_list);
	for (size_t i = 0; i < size - 1; ++i) {
		current = sym_list;
		for (size_t j = 0; j < size - i - 1; ++j) {
			if (sym_name_comp(
				    ((struct s_symbol *)current->content)
					    ->st_name,
				    ((struct s_symbol *)current->next->content)
					    ->st_name) > 0) {
				tmp = current->content;
				current->content = current->next->content;
				current->next->content = tmp;
			}
			current = current->next;
		}
	}
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
	if (ei_class == ELFCLASS32)
		sym_list = parse_32(ptr);
	else if (ei_class == ELFCLASS64)
		sym_list = parse_64(ptr);
	else
		return print_error("Wrong ei_class", NULL);
	sort_sym_list(sym_list);
	ft_lstiter(sym_list, (void (*)(void *))print_sym);
	return 0;
}
