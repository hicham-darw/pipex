#include "libpipex.h"

void	from_file_2_pipe(int fds[], char **av, char *args[], char **env)
{
	char	**cmd;
	char	*pathname;
	int		fd;

	if (!av || !env || !fds)
		exit(EXIT_FAILURE);
	close(fds[0]);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		perror_and_exit(perror, "open failed");
	dup_and_close(fd, STDIN_FILENO);
	cmd = ft_split(av[2], ' ');
	if (!cmd)
		exit(EXIT_FAILURE);
	pathname = get_pathname_execve(cmd[0], env);
	if (!pathname)
		exit(EXIT_FAILURE);
	fill_args_execve(cmd, args);
	if (fd < 0)
		perror_and_exit(perror, "open failed");
	dup_and_close(fds[1], STDOUT_FILENO);
	execve(pathname, args, env);
	ft_delvector(cmd);
	free(pathname);
	exit(EXIT_SUCCESS);
}
