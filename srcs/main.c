#include "ft_nm.h"

void nm(char *ptr)
{
	(void)ptr;
}

int main(int argc, char **argv)
{
	int fd;
	struct stat statbuf;
	char *ptr;
	
	if (argc < 2) {
		fprintf(stderr, "Need argument\n");
		return EXIT_FAILURE;
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		perror("open");
		return EXIT_FAILURE;
	}
	if (fstat(fd, &statbuf) < 0) {
		perror("fstat");
		close(fd);
		return EXIT_FAILURE;
	}
	if ((ptr = mmap(0, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
		perror("mmap");
		close(fd);
		return EXIT_FAILURE;
	}
	nm(ptr);
	if (munmap(ptr, statbuf.st_size) < 0)
	{
		perror("munmap");
		close(fd);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
