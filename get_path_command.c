#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

static void	free_vec(char **vec)
{
	int	i;

	i = 0;
	while (vec[i])
		ft_memdel((void *)&vec[i++]);
	free(vec);
	vec = NULL;
}

char	*get_path_command(char *cmd, char **env)
{
	char	**paths;
	char	*tmp_path;
	int	i, j;

	if (!cmd || !env || !*env)
		return (NULL);
	while (*env)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = ft_split((env[i] + 5), ':');
			j = 0;
			while(paths[j])
			{
				tmp_path = ft_multi_join(3, paths[j], "/",cmd);
				if(access(tmp_path, X_OK) == 0)
				{
					free_vec(paths);
					return (tmp_path);
				}
				j++;
			}
			if(!paths[j])
			{
				free_vec(paths);
				printf("ERROR: %s\n", strerror(errno));
				return (NULL);
			}
		}
		*env++;
	}
}
