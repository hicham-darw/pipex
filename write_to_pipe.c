#include "libpipex.h"

void	write_to_pipe(int fds[], char **av, char **env)
{
	char	**command;
	char	*pathname;
	int		fd;

	close(fds[0]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	dup2_and_close(fd, STDIN_FILENO);
	command = ft_split(av[2], ' ');
	if (!command)
		exit(127);
	pathname = get_pathname_execve(command[0], env);
	if (!pathname)
	{
		fprintf(stderr, "%s: command not found\n", command[0]);
		ft_delvector(command);
		exit(127);
	}
	dup2_and_close(fds[1], STDOUT_FILENO);
	execve(pathname, command, env);
	execve_fails(pathname, command);
}
