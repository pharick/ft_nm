#ifndef FT_NM_H
#define FT_NM_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>
#include <string.h>

struct s_symbol_type_ref {
	int32_t		st_bind;
	int32_t		st_type;
	__int128_t	st_value;
	__int128_t	sh_type;
	char		*sh_name;
	char		symbol;
};

#define GET_SHDRTAB_64(PTR, EHDR) (Elf64_Shdr *)(&PTR[EHDR->e_shoff])

#endif // FT_NM_H
