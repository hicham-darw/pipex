#include "libpipex.h"

int	fork_failed()
{
	printf("fork failed");
	return (1);
}

void	perror_and_exit(void (*perr)(const char *), const char *s)
{
	perr(s);
	exit(EXIT_FAILURE);
}

void	dup_and_close(int fd_file, int fd)
{
	dup2(fd_file, fd);
	close(fd_file);
}
