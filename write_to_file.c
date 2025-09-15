#include "libpipex.h"

void    write_to_file(int fds[], char **av, char **env)
{
    char    **command;
    char    *pathname;
    int fd;

    close(fds[1]);
    fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open failed");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    command = ft_split(av[3], ' ');
    if (!command)
        exit(42);
    pathname = get_pathname_execve(command[0], env);
    if (!pathname)
    {
        fprintf(stderr, "%s: command not found\n", command[0]);
        exit(127);
    }
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
    execve(pathname, command, env);
    ft_delvector(command);
    free(pathname);
    perror("execve");
    exit(1);
}