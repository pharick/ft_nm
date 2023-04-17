#ifndef FT_NM_H
#define FT_NM_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <elf.h>
#include "libft.h"

#define DEFAULT_FILE_PATH "a.out"

struct s_symbol {
	char *st_name;
	uint16_t st_bind;
	uint16_t st_type;
	uint32_t st_value;
	uint16_t st_shndx;
	uint32_t sh_type;
	uint64_t sh_flags;
	char *sh_name;
	int ei_class;
};

struct s_sym_type_ref {
	int32_t st_bind;
	int32_t st_type;
	__int128 st_value;
	int32_t st_shndx;
	__int128 sh_type;
	__int128 sh_flags;
	__int128 sh_flags_not;
	char *sh_name;
	char letter;
};

int nm(const char *ptr, char *path);
t_list *parse_32(const char *ptr);
t_list *parse_64(const char *ptr);
char get_sym_type(struct s_symbol *sym);
int print_error(const char *s, const char *prefix);

#endif // FT_NM_H
