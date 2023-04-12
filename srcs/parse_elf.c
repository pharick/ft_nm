#include "ft_nm.h"

#define GEN_FIND_SECTION_TYPE(__BITS)                                   \
	const Elf##__BITS##_Shdr *find_section_type_##__BITS(           \
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

#define GEN_PARSE_SYM(__BITS)                                            \
	struct s_symbol parse_sym_##__BITS(const Elf##__BITS##_Sym *sym, \
					   const char *strtab) {         \
		struct s_symbol symbol;                                  \
		(void)sym;                                               \
		symbol.name = ft_strdup(&strtab[sym->st_name]);          \
		symbol.value = sym->st_value;                            \
		return symbol;                                           \
	}

GEN_PARSE_SYM(32)
GEN_PARSE_SYM(64)

void parse_64(const char *ptr)
{
	const Elf64_Ehdr *ehdr;
	const Elf64_Shdr *shdrtab;
	size_t shdrtab_size;
	const Elf64_Shdr *symtab_shdr;
	const Elf64_Sym *symtab;
	size_t symtab_size;
	const Elf64_Shdr *strtab_shdr;
	const char *strtab;
	struct s_symbol sym;

	ehdr = (Elf64_Ehdr *)ptr;
	shdrtab = (Elf64_Shdr *)&ptr[ehdr->e_shoff];
	shdrtab_size = ehdr->e_shnum;

	symtab_shdr = find_section_type_64(shdrtab, shdrtab_size, SHT_SYMTAB);
	symtab = (Elf64_Sym *)&ptr[symtab_shdr->sh_offset];
	symtab_size = symtab_shdr->sh_size / symtab_shdr->sh_entsize;

	strtab_shdr = &shdrtab[symtab_shdr->sh_link];
	strtab = &ptr[strtab_shdr->sh_offset];

	for (size_t i = 0; i < symtab_size; ++i) {
		sym = parse_sym_64(&symtab[i], strtab);
		printf("%016lx %s\n", sym.value, sym.name);
	}
}
