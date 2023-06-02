#include "ft_nm.h"

void free_symbol(struct s_symbol *sym)
{
	free(sym->sh_name);
	free(sym->st_name);
	free(sym);
}

void free_sym_list(t_list *syms)
{
	t_list *next;

	while (syms != NULL) {
		next = syms->next;
		free_symbol(syms->content);
		free(syms);
		syms = next;
	}
}

#define GEN_FIND_SECTION_TYPE(__BITS)                                   \
	static const Elf##__BITS##_Shdr *find_section_type_##__BITS(    \
		const Elf##__BITS##_Shdr *shdrtab, size_t shdrtab_size, \
		uint32_t sh_type)                                       \
	{                                                               \
		for (size_t i = 0; i < shdrtab_size; ++i)               \
			if (shdrtab[i].sh_type == sh_type)              \
				return &shdrtab[i];                     \
		return NULL;                                            \
	}

GEN_FIND_SECTION_TYPE(32)
GEN_FIND_SECTION_TYPE(64)

#define GEN_PARSE_SYM(__BITS)                                                  \
	static struct s_symbol *parse_sym_##__BITS(                            \
		const Elf##__BITS##_Sym *sym, const char *strtab,              \
		const Elf##__BITS##_Shdr *shdrtab, const char *shstrtab)       \
	{                                                                      \
		struct s_symbol *symbol;                                       \
                                                                               \
		symbol = (struct s_symbol *)malloc(sizeof(struct s_symbol));   \
		symbol->ei_class = __BITS == 32 ? 1 : 2;                       \
		symbol->st_name = ft_strdup(&strtab[sym->st_name]);            \
		symbol->st_bind = ELF##__BITS##_ST_BIND(sym->st_info);         \
		symbol->st_type = ELF##__BITS##_ST_TYPE(sym->st_info);         \
		symbol->st_value = sym->st_value;                              \
		symbol->st_shndx = sym->st_shndx;                              \
		if (sym->st_shndx != SHN_ABS) {                                \
			const Elf##__BITS##_Shdr *shdr =                       \
				&shdrtab[sym->st_shndx];                       \
			symbol->sh_type = shdr->sh_type;                       \
			symbol->sh_name = ft_strdup(&shstrtab[shdr->sh_name]); \
			symbol->sh_flags = shdr->sh_flags;                     \
		} else {                                                       \
			symbol->sh_type = SHT_NULL;                            \
			symbol->sh_name = ft_strdup("");                       \
			symbol->sh_flags = 0;                                  \
		}                                                              \
		return symbol;                                                 \
	}

GEN_PARSE_SYM(32)
GEN_PARSE_SYM(64)

#define GEN_GET_SYM_LIST(__BITS)                                              \
	static t_list *get_sym_list_##__BITS(                                 \
		const Elf##__BITS##_Sym *symtab, size_t symtab_size,          \
		const char *strtab, const Elf##__BITS##_Shdr *shdrtab,        \
		const char *shstrtab)                                         \
	{                                                                     \
		t_list *list;                                                 \
		struct s_symbol *sym;                                         \
                                                                              \
		list = NULL;                                                  \
		for (size_t i = 0; i < symtab_size; ++i) {                    \
			sym = parse_sym_##__BITS(&symtab[i], strtab, shdrtab, \
						 shstrtab);                   \
			if (sym->st_name[0] != '\0' &&                        \
			    sym->st_shndx != SHN_ABS)                         \
				ft_lstadd_front(&list, ft_lstnew(sym));       \
			else                                                  \
				free_symbol(sym);                             \
		}                                                             \
		return list;                                                  \
	}

GEN_GET_SYM_LIST(32)
GEN_GET_SYM_LIST(64)

#define GEN_PARSE(__BITS)                                                     \
	t_list *parse_##__BITS(const char *ptr, char *path, struct stat s)    \
	{                                                                     \
		const Elf##__BITS##_Ehdr *ehdr;                               \
		const Elf##__BITS##_Shdr *shdrtab;                            \
		size_t shdrtab_size;                                          \
		const Elf##__BITS##_Shdr *symtab_shdr;                        \
		const Elf##__BITS##_Sym *symtab;                              \
		size_t symtab_size;                                           \
		const Elf##__BITS##_Shdr *strtab_shdr;                        \
		const char *strtab;                                           \
		const Elf##__BITS##_Shdr *shstrtab_shdr;                      \
		const char *shstrtab;                                         \
		t_list *sym_list;                                             \
                                                                              \
		ehdr = (Elf##__BITS##_Ehdr *)ptr;                             \
		shdrtab = (Elf##__BITS##_Shdr *)&ptr[ehdr->e_shoff];          \
		shdrtab_size = ehdr->e_shnum;                                 \
		if (ehdr->e_shoff > (long unsigned int)s.st_size ||           \
		    ehdr->e_shoff + shdrtab_size * ehdr->e_shentsize >        \
			    (long unsigned int)s.st_size) {                   \
			print_error("file too short", path);                  \
			return NULL;                                          \
		}                                                             \
		symtab_shdr = find_section_type_##__BITS(                     \
			shdrtab, shdrtab_size, SHT_SYMTAB);                   \
		if (!symtab_shdr)                                             \
			return NULL;                                          \
		symtab = (Elf##__BITS##_Sym *)&ptr[symtab_shdr->sh_offset];   \
		symtab_size = symtab_shdr->sh_size / symtab_shdr->sh_entsize; \
		strtab_shdr = &shdrtab[symtab_shdr->sh_link];                 \
		strtab = &ptr[strtab_shdr->sh_offset];                        \
		shstrtab_shdr = &shdrtab[ehdr->e_shstrndx];                   \
		shstrtab = &ptr[shstrtab_shdr->sh_offset];                    \
		sym_list = get_sym_list_##__BITS(symtab, symtab_size, strtab, \
						 shdrtab, shstrtab);          \
		return sym_list;                                              \
	}

GEN_PARSE(32)
GEN_PARSE(64)
