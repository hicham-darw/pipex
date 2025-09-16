#include "libpipex.h"

void	write_to_file(int fds[], char **av, char **env)
{
	char	**command;
	char	*pathname;
	int		fd;

	close(fds[1]);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(av[4]);
		exit(1);
	}
	dup2_and_close(fd, STDOUT_FILENO);
	command = ft_split(av[3], ' ');
	if (!command)
		exit(1);
	pathname = get_pathname_execve(command[0], env);
	if (!pathname)
	{
		put_command_not_found("command not found", command[0]);
		ft_delvector(command);
		exit(127);
	}
	dup2_and_close(fds[0], STDIN_FILENO);
	execve(pathname, command, env);
	execve_fails(pathname, command);
}
