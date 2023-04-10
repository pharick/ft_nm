#ifndef LIBFT_H
#define LIBFT_H

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

size_t ft_strlen(const char *s);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strdup(const char *s1);
int ft_strcmp(const char *s1, const char *s2);
void ft_putchar_fd(char c, int fd);
void ft_putstr_fd(const char *s, int fd);

#endif // LIBFT_H
