#include "libpipex.h"

int	main(int ac, char **av, char **env)
{
	int		fds[2];
	pid_t	pid1, pid2;
	int status1, status2;

	if (ac != 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", STDERR_FILENO);
		return (1);
	}
	//leaks ... norminette
	pipe(fds);
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid1 == 0)
		write_to_pipe(fds, av, env);
	
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid2 == 0)
		write_to_file(fds, av, env);
	close(fds[1]);
	close(fds[0]);
	waitpid(pid1, &status1, 0);
	int wst = 0;
	if (WIFEXITED(status1))
		wst = WEXITSTATUS(status1);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		wst = WEXITSTATUS(status2);
	return (wst);
}
