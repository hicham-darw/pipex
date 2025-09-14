#ifndef LIBPIPEX_H
# define LIBPIPEX_H

# include "libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

void	from_file_2_pipe(int fds[], char **av, char *args[], char **env);
void	from_pipe_2_file(int fds[], char **av, char *args[], char **env);
char	*get_pathname_execve(char *cmd, char **env);
int	fork_failed(void (*perr)(const char *));
void	perror_and_exit(void (*perr)(const char *), const char *s);
void	fill_args_execve(char **cmd, char *args[]);
void	dup_and_close(int old_fd, int new_fd);

# endif
