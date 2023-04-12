#include "ft_nm.h"

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

#define GEN_PARSE_SYM(__BITS)                                         \
	static struct s_symbol parse_sym_##__BITS(                    \
		const Elf##__BITS##_Sym *sym, const char *strtab) {   \
		struct s_symbol symbol;                               \
                                                                      \
		symbol.st_name = ft_strdup(&strtab[sym->st_name]);    \
		symbol.st_bind = ELF##__BITS##_ST_BIND(sym->st_info); \
		symbol.st_type = ELF##__BITS##_ST_TYPE(sym->st_info); \
		symbol.st_value = sym->st_value;                      \
		return symbol;                                        \
	}

GEN_PARSE_SYM(32)
GEN_PARSE_SYM(64)

#define GEN_PARSE(__BITS)                                                     \
	void parse_##__BITS(const char *ptr)                                  \
	{                                                                     \
		const Elf##__BITS##_Ehdr *ehdr;                               \
		const Elf##__BITS##_Shdr *shdrtab;                            \
		size_t shdrtab_size;                                          \
		const Elf##__BITS##_Shdr *symtab_shdr;                        \
		const Elf##__BITS##_Sym *symtab;                              \
		size_t symtab_size;                                           \
		const Elf##__BITS##_Shdr *strtab_shdr;                        \
		const char *strtab;                                           \
		struct s_symbol sym;                                          \
                                                                              \
		ehdr = (Elf##__BITS##_Ehdr *)ptr;                             \
		shdrtab = (Elf##__BITS##_Shdr *)&ptr[ehdr->e_shoff];          \
		shdrtab_size = ehdr->e_shnum;                                 \
                                                                              \
		symtab_shdr = find_section_type_##__BITS(                     \
			shdrtab, shdrtab_size, SHT_SYMTAB);                   \
		symtab = (Elf##__BITS##_Sym *)&ptr[symtab_shdr->sh_offset];   \
		symtab_size = symtab_shdr->sh_size / symtab_shdr->sh_entsize; \
                                                                              \
		strtab_shdr = &shdrtab[symtab_shdr->sh_link];                 \
		strtab = &ptr[strtab_shdr->sh_offset];                        \
                                                                              \
		for (size_t i = 0; i < symtab_size; ++i) {                    \
			sym = parse_sym_##__BITS(&symtab[i], strtab);         \
			printf("%016x, %s, %d, %d\n", sym.st_value,           \
			       sym.st_name, sym.st_bind, sym.st_type);        \
		}                                                             \
	}

GEN_PARSE(32)
GEN_PARSE(64)
