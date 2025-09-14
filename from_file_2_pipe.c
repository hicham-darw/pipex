#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void	exit_by_error(void (*f)(const char *str));

void	fill_args_execve(char **cmd, char *args[])
{
	if (!cmd)
		exit_by_error(perror);
	args[0] = cmd[0];
	args[1] = cmd[1];
	args[2] = NULL;
}

void	dup_and_close(int fd_file, int fd)
{
	dup2(fd_file, fd);
	close(fd_file);
}

char	*get_pathname_execve(char *cmd, char **env);
void	free_vec(char **vec);

void	from_file_2_pipe(int fds[], char **av, char *args[], char **env)
{
	char	**cmd;
	char	*pathname;
	int		fd;

	if (!av || !env || !fds)
		exit_by_error(perror);
	close(fds[0]);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit_by_error(perror);
	dup_and_close(fd, STDIN_FILENO);
	cmd = ft_split(av[2], ' ');
	if (!cmd)
		exit_by_error(perror);
	pathname = get_pathname_execve(cmd[0], env);
	if (!pathname)
		exit_by_error(perror);
	fill_args_execve(cmd, args);
	if (fd < 0)
		exit_by_error(perror);
	dup_and_close(fds[1], STDOUT_FILENO);
	execve(pathname, args, env);
	free_vec(cmd);
	free(pathname);
	exit(EXIT_SUCCESS);
}
