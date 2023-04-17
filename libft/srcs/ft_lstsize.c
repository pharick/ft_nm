#include "libft.h"

size_t ft_lstsize(t_list *lst)
{
	size_t size;
	t_list *node;

	size = 0;
	node = lst;
	while (node) {
		++size;
		node = node->next;
	}
	return size;
}
