# ft_nm

A reimplementation of the `nm` symbol-listing tool for ELF binaries, written in C for the École 42 `nm` project.

`ft_nm` memory-maps an ELF file, walks its section header table to find `.symtab` and the associated string tables, decodes every symbol's binding, type, section and value into the one-letter classification that GNU `nm` prints (`T`, `t`, `D`, `d`, `B`, `b`, `R`, `r`, `U`, `W`, `w`, `V`, `v`, `u`, `n`), sorts the symbols the way `nm` does, and prints them with an 8- or 16-digit hexadecimal address. Both ELF32 and ELF64 are supported from the same code, and malformed files are rejected with an error instead of a crash.

## Highlights

- One parser for both ELF classes: `parse_elf.c` defines the section lookup, symbol decoding and symbol-list builder as macros (`GEN_FIND_SECTION_TYPE`, `GEN_PARSE_SYM`, `GEN_GET_SYM_LIST`, `GEN_PARSE`) that are instantiated for `32` and `64`, using `Elf32_*`/`Elf64_*` types from `<elf.h>`; the printer then only needs `ei_class` to choose the address width.
- Symbol classification is data, not a chain of `if`s: `symbol_type.c` holds a table of `s_sym_type_ref` rules (binding, type, section index, section type, required and forbidden section flags, section name, output letter) with `-1` as a wildcard; `get_sym_type()` returns the letter of the first matching rule and `?` otherwise. Adding a case is one table entry.
- Sorting matches GNU `nm`: names are compared after dropping `_`, `@` and `.` and lower-casing (`ft_strdup_ex`), with the address as a tie-breaker; undefined and weak-undefined symbols get a blank address column of the right width.
- The file is read with `open` + `fstat` + `mmap(PROT_READ, MAP_PRIVATE)`, and the section header table offset and size are checked against `st_size` before any dereference, so truncated headers produce `nm: <file>: file too short` rather than a segfault.
- Errors are reported in `nm`'s own format (`nm: <path>: <message>`) on fd 2 with a non-zero exit code; with several arguments each file is printed under a `<path>:` heading and the return code is the count of failures.
- The Makefile generates `.d` dependency files with `gcc -M` and `-include`s them, so header edits trigger correct rebuilds; the code is formatted with the repository `.clang-format` (8-wide tabs, kernel-style braces).

## How it works

```
main.c        open/fstat/mmap each path (default a.out) -> nm()
  |
nm.c          check ELFMAG, dispatch on EI_CLASS -> parse_32 / parse_64
  |           sort_sym_list (bubble sort on t_list, nm ordering)
  |           print_sym (address | blank, letter, name)
  |
parse_elf.c   e_shoff bounds check -> find SHT_SYMTAB -> strtab (sh_link)
              -> shstrtab (e_shstrndx) -> one s_symbol per Elf_Sym
  |
symbol_type.c get_sym_type(): rule table -> letter
errors.c      print_error(): "nm: prefix: message"
```

Per symbol the parser records `st_name`, `st_bind`, `st_type`, `st_value`, `st_shndx`, and from the referenced section its `sh_type`, `sh_flags` and `sh_name`; unnamed symbols and `SHN_ABS` symbols are dropped, as in the default `nm` output.

## Building and running

```bash
make          # builds libft/libft.a and ./nm
./nm          # lists symbols of ./a.out
./nm file
./nm file1 file2 ...
```

Requires `gcc`, `make`, and a system `<elf.h>` (Linux). `make clean` also removes the generated `.d` files; `make fclean` and `make re` are available.

## Testing

`test.sh` runs the binary and the system `nm` on the same arguments and diffs their output:

```bash
./test.sh /bin/ls
./test.sh tests/error_header
```

`tests/` contains small C sources (`easy_test.c`, `not_so_easy_test.c`, `test.c`) intended to be compiled into 32- and 64-bit binaries (`.gitignore` reserves `test32`, `test64`, `tests/*_test_32`, `tests/*_test_64`), plus hand-crafted ELF files that exercise the error paths:

| File | What it is |
| --- | --- |
| `header`, `header_copy` | Just a 64-byte ELF64 header, no section headers |
| `header_and_prog`, `header_and_prog_copy` | Header plus one program header, section table offset beyond EOF |
| `wrong_arch` | `EI_CLASS` byte set to 32-bit on an otherwise 64-bit layout |
| `error_header`, `header_offset_error` | Full executables with a corrupted section header offset/size |
| `unterminated_string` | Executable whose string table is not NUL-terminated |

## Limitations / notes

- Only little-endian files in the host byte order are decoded; `EI_DATA` is not inspected and no byte swapping is done.
- No command-line options (`-a`, `-g`, `-u`, `-r`, `-p`, `-n`) are implemented; output is always the default `nm` listing.
- Bounds checks cover the section header table; offsets inside individual sections (`sh_offset`, `sh_link`, `st_name`) are trusted, so a deliberately corrupt file can still read out of the mapping.
- Sorting is an O(n^2) bubble sort over a linked list, which is slow on binaries with tens of thousands of symbols.
- Requires `<elf.h>`, so it builds on Linux only.

## Context

École 42 `nm` project (Unix branch, 2023): reimplement `nm` for ELF32/ELF64 executables, objects and shared libraries without `libelf`, handling wrong or corrupted files without crashing. The allowed functions were `open`, `close`, `mmap`, `munmap`, `write`, `fstat`, `malloc`, `free`, `exit`, `errno`, `strerror` and `perror`.
