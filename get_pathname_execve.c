#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

void	free_vec(char **vec)
{
	int	i;

	i = 0;
	while (vec[i])
		ft_memdel((void *)&vec[i++]);
	free(vec);
	vec = NULL;
}

char	*find_pathname(char **paths, char *cmd)
{
	char	*pathname;

	if (!paths || !*paths || !cmd)
		return (NULL);
	while (*paths)
	{
		pathname = ft_multi_join(3, *paths, "/", cmd);
		if (!pathname)
			return (NULL);
		if (access(pathname, X_OK) == 0)
			return (pathname);
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
				free_vec(paths);
				perror("Error: ");
				return (NULL);
			}
			free_vec(paths);
			return (pathname);
		}
		i++;
	}
	return (NULL);
}
