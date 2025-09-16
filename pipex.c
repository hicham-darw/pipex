#include "libpipex.h"

int	main(int ac, char **av, char **env)
{
	int		fds[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (ac != 5)
		return (put_usage());
	pipe(fds);
	pid1 = fork();
	if (pid1 == -1)
		return (fork_fails());
	else if (pid1 == 0)
		write_to_pipe(fds, av, env);
	pid2 = fork();
	if (pid2 == -1)
		return (fork_fails());
	else if (pid2 == 0)
		write_to_file(fds, av, env);
	close(fds[1]);
	close(fds[0]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
}
