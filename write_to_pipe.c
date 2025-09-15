#include "libpipex.h"

void    write_to_pipe(int fds[], char **av, char **env)
{
    char    **command;
    char    *pathname;
    int     fd;

    close(fds[0]);
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        perror("open failed");
        exit(42);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    command = ft_split(av[2], ' ');
    if (!command)
    {
        perror("split");
        exit(1);
    }
    pathname = get_pathname_execve(command[0], env);
    if (!pathname)
    {
        fprintf(stderr, "%s: command not found\n", command[0]);
        exit(127);
    }
    //here
    dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    execve(pathname, command, env);
    ft_delvector(command);
    free(pathname);
    perror("execve");
    exit(1);
}