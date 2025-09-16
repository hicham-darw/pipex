#include "libpipex.h"

static char	*find_pathname(char **paths, char *cmd)
{
	char	*pathname;

	if (!paths || !*paths || !cmd)
		return (NULL);
	while (*paths)
	{
		pathname = ft_multi_join(3, *paths, "/", cmd);
		if (!pathname)
		{
			perror("multijoin");
			exit(1);
		}
		if (access(pathname, X_OK) == 0)
			return (pathname);
		else
			free(pathname);
		paths++;
	}
	return (NULL);
}

char	*get_pathname_execve(char *cmd, char **env)
{
	char	**paths;
	char	*pathname;
	int		i;

	if (!cmd || !env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split((env[i] + 5), ':');
			pathname = find_pathname(paths, cmd);
			if (!pathname)
			{
				ft_delvector(paths);
				return (NULL);
			}
			ft_delvector(paths);
			return (pathname);
		}
		i++;
	}
	return (NULL);
}
