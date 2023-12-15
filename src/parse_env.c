#include "pipex.h"

static char	**add_slashes(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		paths[i] = join_free(paths[i], "/");
		if (!paths[i])
		{
			free_split(paths);
			break ;
		}
		++i;
	}
	return (paths);
}

char	**get_env_path_line(char **env)
{
	int		i;
	char	**res;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH=") == env[i])
		{
			res = ft_split(env[i] + ft_strlen("PATH="), ':');
			break ;
		}
		++i;
	}
	i = 0;
	res = add_slashes(res);
	return (res);
}
