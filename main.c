#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

char	*get_path_command(char *cmd, char **env);

int	main(int ac, char **av, char **env)
{
	char	*path, **cmd1, **cmd2, *args[6];
	pid_t pid1, pid2;
	
	int	fds[2], fd;

	if (ac != 5)
		return (EXIT_FAILURE);
	pipe(fds);
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	pid1 = fork();
	if (pid1 < 0 || pid2 < 0)
	{
		perror("pid: ");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		path = get_path_command(cmd1[0], env);
		if (!path)
			exit(1);
		sleep(2);
		args[0] = cmd1[0];
		args[1] = cmd1[1];
		args[2] = av[1];
		args[3] = NULL;
		execve(path, args, env);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		fd = open(av[4], O_WRONLY | O_CREAT, 0777);
		if (fd < 0)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		path = get_path_command(cmd2[0], env);
		if (!path)
			exit(1);
		args[0] = cmd2[0];
		args[1] = cmd2[1];
		args[3] = NULL;
		execve(path, args, env);
		exit(0);
	}
	wait(NULL);
	close(fds[0]);
	close(fds[1]);
}
