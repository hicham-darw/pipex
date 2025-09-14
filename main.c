#include "libpipex.h"

int	main(int ac, char **av, char **env)
{
	char	*args[4];
	int		fds[2];
	pid_t	pid;

	if (ac != 5)
	{
		printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	pipe(fds);
	pid = fork();
	if (pid < 0)
		return (fork_failed(perror));
	if (pid == 0)
		from_file_2_pipe(fds, av, args, env);
	pid = fork();
	if (pid < 0)
		return (fork_failed(perror));
	if (pid == 0)
		from_pipe_2_file(fds, av, args, env);
	close(fds[1]);
	close(fds[0]);
	wait(NULL);
	return (0);
}
