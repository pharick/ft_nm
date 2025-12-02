# ft_nm Project Code Review

## Overview
This is an implementation of the `nm` utility, which lists symbols from ELF binary files. The project supports both 32-bit and 64-bit ELF files and includes basic error handling.

## Test Results

### Memory Safety
✅ **Valgrind**: No memory leaks detected (6,248 allocs, 6,248 frees)
✅ **AddressSanitizer/UBSanitizer**: No issues detected
✅ **Basic functionality**: Works on valid ELF files

### Compatibility
⚠️ **Symbol Sorting**: Output differs from system `nm` in symbol ordering

---

## Critical Issues

### 1. **Buffer Overflow Risk in parse_elf.c** (HIGH SEVERITY)
**Location**: `srcs/parse_elf.c:52`

```c
if (sym->st_shndx != SHN_ABS) {
    const Elf##__BITS##_Shdr *shdr = &shdrtab[sym->st_shndx];  // ⚠️ No bounds checking
```

**Issue**: The code accesses `shdrtab[sym->st_shndx]` without validating that `sym->st_shndx` is within bounds (0 to `shdrtab_size`). While there's a check for section headers at lines 110-115, there's no validation that individual symbol's `st_shndx` values are valid indices.

**Risk**: A malformed ELF file could have `st_shndx` pointing beyond the section header table, causing a buffer overflow read.

**Recommendation**:
```c
if (sym->st_shndx != SHN_ABS && sym->st_shndx < shdrtab_size) {
    const Elf##__BITS##_Shdr *shdr = &shdrtab[sym->st_shndx];
    // ...
} else {
    symbol->sh_type = SHT_NULL;
    symbol->sh_name = ft_strdup("");
    symbol->sh_flags = 0;
}
```

---

### 2. **Integer Overflow in Symbol Comparison** (MEDIUM SEVERITY)
**Location**: `srcs/nm.c:55`

```c
value_cmp = curr_symb->st_value - next_symb->st_value;  // ⚠️ Can overflow
```

**Issue**: Direct subtraction of two `uint32_t` values can cause integer overflow if the difference exceeds INT_MAX or goes negative.

**Recommendation**:
```c
if (curr_symb->st_value < next_symb->st_value)
    value_cmp = -1;
else if (curr_symb->st_value > next_symb->st_value)
    value_cmp = 1;
else
    value_cmp = 0;
```

---

### 3. **Potential String Access Out of Bounds** (MEDIUM SEVERITY)
**Location**: `srcs/parse_elf.c:45, 54, 123-125`

**Issue**: String table accesses like `&strtab[sym->st_name]` and `&shstrtab[shdr->sh_name]` don't validate that:
- The offset is within the string table section bounds
- The string is null-terminated before the section ends

**Risk**: A malformed ELF could cause reading beyond allocated memory.

**Recommendation**: Add bounds checking for all string table accesses:
```c
// Before accessing strings
if (sym->st_name >= strtab_shdr->sh_size) {
    // handle error
}
// Ensure null termination exists within bounds
size_t max_len = strtab_shdr->sh_size - sym->st_name;
```

---

### 4. **Missing Bounds Check for Section Header Offsets** (MEDIUM SEVERITY)
**Location**: `srcs/parse_elf.c:120, 123-125`

```c
symtab = (Elf##__BITS##_Sym *)&ptr[symtab_shdr->sh_offset];
strtab = &ptr[strtab_shdr->sh_offset];
shstrtab = &ptr[shstrtab_shdr->sh_offset];
```

**Issue**: While the section header table itself is validated, individual section offsets (`sh_offset`) and sizes aren't checked against the file size.

**Recommendation**: Add validation:
```c
if (symtab_shdr->sh_offset + symtab_shdr->sh_size > (size_t)s.st_size ||
    strtab_shdr->sh_offset + strtab_shdr->sh_size > (size_t)s.st_size ||
    shstrtab_shdr->sh_offset + shstrtab_shdr->sh_size > (size_t)s.st_size) {
    print_error("corrupted section headers", path);
    return NULL;
}
```

---

## Functional Issues

### 5. **Incorrect Symbol Sorting** (MEDIUM PRIORITY)
**Location**: `srcs/nm.c:21-33, 35-64`

**Issue**: The sorting algorithm doesn't match GNU `nm` output. Comparison of outputs shows:
- System `nm` groups symbols differently
- The custom `sym_name_comp` function may not handle all edge cases correctly

**System nm output**:
```
_DYNAMIC
_GLOBAL_OFFSET_TABLE_
_IO_stdin_used
```

**ft_nm output**:
```
__abi_tag
__bss_start
close@GLIBC_2.2.5
```

**Root cause**: The `sym_name_comp` function removes "_@." characters and compares, but this doesn't match GNU nm's sorting algorithm which uses a more sophisticated locale-aware comparison.

---

### 6. **Inefficient Sorting Algorithm** (LOW PRIORITY)
**Location**: `srcs/nm.c:35-64`

**Issue**: Uses bubble sort with O(n²) complexity.

**Impact**: Performance degradation on binaries with thousands of symbols.

**Recommendation**: Consider using a more efficient algorithm like quicksort or mergesort (O(n log n)), or use `qsort()` from stdlib.

---

## Code Quality Issues

### 7. **Magic Numbers and Hardcoded Values**
**Examples**:
- `parse_elf.c:44`: `symbol->ei_class = __BITS == 32 ? 1 : 2;`
  - Should use `ELFCLASS32` and `ELFCLASS64` constants

### 8. **Inconsistent Error Handling**
**Location**: `srcs/parse_elf.c:113-115, 118-119`

**Issue**:
- Line 113: Prints error and returns NULL
- Line 118: Only returns NULL without printing error

**Recommendation**: Consistent error reporting for all failure cases.

### 9. **Limited Symbol Filtering**
**Location**: `srcs/parse_elf.c:80-84`

```c
if (sym->st_name[0] != '\0' && sym->st_shndx != SHN_ABS)
    ft_lstadd_front(&list, ft_lstnew(sym));
else
    free_symbol(sym);
```

**Issue**: Filters out `SHN_ABS` symbols completely, but many `nm` implementations include absolute symbols with the 'A' type.

---

### 10. **No Support for Additional nm Features**
Missing features commonly found in `nm`:
- `-a` flag: Show all symbols including debugger symbols
- `-g` flag: Show only external symbols
- `-u` flag: Show only undefined symbols
- `-r` flag: Reverse sort order
- `-p` flag: Don't sort (show in symbol table order)
- Support for archive files (.a)
- Support for dynamic symbol tables (`.dynsym`)

---

## Minor Issues

### 11. **C99 Style Loop Declaration**
**Location**: `srcs/main.c:41`

```c
for (int i = 1; i < argc; ++i)  // C99 feature
```

**Note**: This is fine if targeting C99+, but older C89/C90 compilers won't accept this.

### 12. **Unused Return Values**
**Location**: `srcs/main.c:45`

```c
ret += process_file(argv[i]);  // Accumulates but behavior unclear
```

**Issue**: It's unclear what the intended behavior is when multiple files fail. Should it stop on first error or continue?

---

### 13. **Missing Documentation**
- No README explaining how to build and use
- No comments explaining the symbol type matching algorithm
- No documentation of supported ELF features

---

## Positive Aspects

✅ **Clean memory management**: No leaks detected
✅ **Good macro use**: Generic macros for 32/64-bit avoid code duplication
✅ **Basic error handling**: Handles file access errors, invalid formats
✅ **Separation of concerns**: Clean modular structure
✅ **Bounds checking**: Some validation present for section headers

---

## Priority Recommendations

### Must Fix (Security)
1. Add bounds checking for `st_shndx` in parse_sym functions
2. Validate all string table accesses
3. Validate section offsets and sizes
4. Fix integer overflow in value comparison

### Should Fix (Correctness)
1. Fix symbol sorting to match GNU nm output
2. Make error handling consistent

### Nice to Have (Enhancement)
1. Implement more efficient sorting
2. Add support for common nm flags
3. Add support for dynamic symbol tables
4. Add comprehensive documentation
5. Add test suite comparing output with system nm

---

## Testing Recommendations

1. **Fuzz testing**: Use AFL or libFuzzer with malformed ELF files
2. **Boundary testing**: Create ELF files with edge cases:
   - Maximum section count
   - Symbols with large `st_shndx` values
   - Unterminated strings in string tables
   - Sections at maximum file offsets
3. **Comparison testing**: Systematic comparison with GNU nm across many binaries
4. **Performance testing**: Test with large binaries (thousands of symbols)

---

## Conclusion

The implementation is functional and demonstrates good understanding of ELF format parsing. However, it has several security vulnerabilities related to insufficient bounds checking that should be addressed before use on untrusted input. The sorting algorithm differs from GNU nm and should be corrected for compatibility.

**Overall Grade**: B-
- Security: C (vulnerabilities present)
- Functionality: B (works but sorting incorrect)
- Code Quality: B+ (clean, maintainable)
- Completeness: C (missing many nm features)
