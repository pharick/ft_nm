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
	char *name;
	uint64_t value;
};

struct s_symbol_type_ref {
	int32_t st_bind;
	int32_t st_type;
	__int128_t st_value;
	__int128_t sh_type;
	char *sh_name;
	char symbol;
};

int nm(const char *ptr, char *path);
void parse_32(const char *ptr);
void parse_64(const char *ptr);

int print_error(const char *s, const char *prefix);

#endif // FT_NM_H
