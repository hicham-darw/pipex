#include "libpipex.h"

void	from_pipe_2_file(int fds[], char **av, char *args[], char **env)
{
	char	**cmd;
	char	*pathname;
	int		fd;

	if (!env || !fds || !av)
		exit(EXIT_FAILURE);
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror_and_exit(perror, "open failed");
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cmd = ft_split(av[3], ' ');
	if (!cmd)
		exit(EXIT_FAILURE);
	pathname = get_pathname_execve(cmd[0], env);
	if (!pathname)
		exit(EXIT_FAILURE);
	args[0] = cmd[0];
	args[1] = cmd[1];
	args[2] = NULL;
	execve(pathname, args, env);
	exit(EXIT_SUCCESS);
}
