#include "ft_nm.h"

static struct s_sym_type_ref symbol_type_ref[] = {
	{
		.st_bind = STB_WEAK,
		.st_type = STT_OBJECT,
		.st_value = 0,
		.sh_type = -1,
		.sh_name = "",
		.letter = 'v',
	},
	{
		.st_bind = STB_WEAK,
		.st_type = STT_OBJECT,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = "",
		.letter = 'V',
	},
	{
		.st_bind = STB_WEAK,
		.st_type = -1,
		.st_value = 0,
		.sh_type = -1,
		.sh_name = "",
		.letter = 'w',
	},
	{
		.st_bind = STB_WEAK,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = "",
		.letter = 'W',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = SHT_NOBITS,
		.sh_name = "",
		.letter = 'b',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = SHT_NOBITS,
		.sh_name = "",
		.letter = 'B',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".data",
		.letter = 'd',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".data",
		.letter = 'D',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".fini_array",
		.letter = 'd',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".fini_array",
		.letter = 'D',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".init_array",
		.letter = 'd',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".init_array",
		.letter = 'D',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".dynamic",
		.letter = 'd',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".dynamic",
		.letter = 'D',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".got.plt",
		.letter = 'd',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".got.plt",
		.letter = 'D',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".text",
		.letter = 't',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".text",
		.letter = 'T',
	},
	{
		.st_bind = STB_LOCAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".init",
		.letter = 't',
	},
	{
		.st_bind = STB_GLOBAL,
		.st_type = -1,
		.st_value = -1,
		.sh_type = -1,
		.sh_name = ".init",
		.letter = 'T',
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
		    (ref.sh_type == -1 || ref.sh_type == sym->sh_type) &&
		    (ft_strlen(ref.sh_name) == 0 ||
		     ft_strcmp(ref.sh_name, sym->sh_name) == 0))
			return ref.letter;
	}
	return ' ';
}
