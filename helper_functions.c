#include "libpipex.h"

int	fork_failed(void (*perr)(const char *))
{
	perr("fork failed");
	return (1);
}

void	perror_and_exit(void (*perr)(const char *), const char *s)
{
	perr(s);
	exit(EXIT_FAILURE);
}

void	fill_args_execve(char **cmd, char *args[])
{
	if (!cmd)
		perror_and_exit(perror, "Error");
	args[0] = cmd[0];
	args[1] = cmd[1];
	args[2] = NULL;
}

void	dup_and_close(int fd_file, int fd)
{
	dup2(fd_file, fd);
	close(fd_file);
}
