#ifndef LIBPIPEX_H
# define LIBPIPEX_H

# include "libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

void	write_to_pipe(int fds[], char **av, char **env);
void	write_to_file(int fds[], char **av, char **env);
char	*get_pathname_execve(char *cmd, char **env);
int		fork_failed();
void	perror_and_exit(void (*perr)(const char *), const char *s);
void	fill_args_execve(char **cmd, char *args[]);
void	dup_and_close(int old_fd, int new_fd);

#endif
