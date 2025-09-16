#include "libpipex.h"

int	fork_fails(void)
{
	perror("fork failed");
	return (1);
}

void	dup2_and_close(int fd_file, int fd)
{
	dup2(fd_file, fd);
	close(fd_file);
}

void	execve_fails(char *pathname, char **args)
{
	free(pathname);
	ft_delvector(args);
	perror("execve");
	exit(1);
}

void	put_command_not_found_fd(char *err_msg, char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
}

int	put_usage(void)
{
	ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2);
	return (1);
}
