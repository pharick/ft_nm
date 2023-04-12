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
	{},
};

char get_sym_type()
{
	for (size_t i = 0; symbol_type_ref[i].letter != 0; ++i) {
		// if ()
	}
	return ' ';
}
