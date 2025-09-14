#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

void	free_vec(char **vec);
void	from_file_2_pipe(int fds[], char **av, char *args[], char **env);
void	from_pipe_2_file(int fds[], char **av, char *args[], char **env);

void	exit_by_error(void (*perr)(const char *))
{
	perr("Error: ");
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{
	char	*args[4];
	int		fds[2];
	pid_t	pid;

	if (ac != 5)
		exit_by_error(perror);
	pipe(fds);
	pid = fork();
	if (pid < 0)
		exit_by_error(perror);
	if (pid == 0)
		from_file_2_pipe(fds, av, args, env);
	pid = fork();
	if (pid < 0)
		exit_by_error(perror);
	if (pid == 0)
		from_pipe_2_file(fds, av, args, env);
	close(fds[1]);
	close(fds[0]);
	wait(NULL);
}
