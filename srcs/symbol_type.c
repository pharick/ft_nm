#include "ft_nm.h"

static struct s_sym_type_ref symbol_type_ref[] = {
	{
		.st_bind = STB_WEAK,
		.st_type = STT_OBJECT,
		.st_value = -1,
		.st_shndx = SHN_UNDEF,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'v',
	},
	{
		.st_bind = STB_WEAK,
		.st_type = STT_OBJECT,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'V',
	},
	{
		.st_bind = STB_WEAK,
		.st_type = -1,
		.st_shndx = SHN_UNDEF,
		.st_value = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'w',
	},
	{
		.st_bind = STB_WEAK,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'W',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = SHT_NOBITS,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'b',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = SHT_NOBITS,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'B',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = 0,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'u',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = 0,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'U',
	},
	{
		.st_bind = -1,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = SHF_WRITE,
		.sh_name = ".group",
		.letter = 'n',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = ".text",
		.letter = 't',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = ".text",
		.letter = 'T',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = ".exit.text",
		.letter = 't',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = ".exit.text",
		.letter = 'T',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = ".init.text",
		.letter = 't',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = ".init.text",
		.letter = 'T',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = ".init",
		.letter = 't',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = ".init",
		.letter = 'T',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = ".fini",
		.letter = 't',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = ".fini",
		.letter = 'T',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = SHF_WRITE,
		.sh_name = "",
		.letter = 'r',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = -1,
		.sh_flags = -1,
		.sh_flags_not = SHF_WRITE,
		.sh_name = "",
		.letter = 'R',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = SHT_PROGBITS,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'd',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = SHT_PROGBITS,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'D',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = SHT_DYNAMIC,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'd',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = SHT_DYNAMIC,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'D',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = SHT_INIT_ARRAY,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'd',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = SHT_INIT_ARRAY,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'D',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = SHT_FINI_ARRAY,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'd',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.st_shndx = -1,
		.sh_type = SHT_FINI_ARRAY,
		.sh_flags = -1,
		.sh_flags_not = -1,
		.sh_name = "",
		.letter = 'D',
	},
	{},
};

char get_sym_type(struct s_symbol *sym)
{
	struct s_sym_type_ref ref;

	for (size_t i = 0; symbol_type_ref[i].letter != 0; ++i) {
		ref = symbol_type_ref[i];
		if ((ref.st_bind == -1 || ref.st_bind == sym->st_bind) &&
		    (ref.st_type == -1 || ref.st_type == sym->st_type) &&
		    (ref.st_value == -1 || ref.st_value == sym->st_value) &&
		    (ref.st_shndx == -1 || ref.st_shndx == sym->st_shndx) &&
		    (ref.sh_type == -1 || ref.sh_type == sym->sh_type) &&
		    (ref.sh_flags == -1 ||
		     (sym->sh_flags & ref.sh_flags) != 0) &&
		    (ref.sh_flags_not == -1 ||
		     (sym->sh_flags & ref.sh_flags_not) == 0) &&
		    (ft_strlen(ref.sh_name) == 0 ||
		     ft_strcmp(ref.sh_name, sym->sh_name) == 0))
			return ref.letter;
	}
	return '?';
}
