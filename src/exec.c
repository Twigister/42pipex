#include <unistd.h>
#include "pipex.h"
/*
static int	count_quotes(char *s)
{
	int	res;

	res = 0;
	while (*s)
	{
		if (*s == '\'')
			++res;
		++s;
	}
	return (res);
}

// Only handles single quotes, not so sorry tho
char	**handle_quotes(char **command)
{
	int	i;
	int	j;

	i = 0;
	while (command[i])
	{
		j = i;
		while (count_quotes(command[i]) % 2)
		{
			++j;
			command[i] = join_free(command[i], command[j]);
		}
		if (i != j)
			replace_words();
	}
}
*/

int	test_bin_access(char *command, char **env)
{
	char	**commands;
	int		ret;
	char	**paths;
	int		i;

	ret = -1;
	i = 0;
	commands = ft_split(command, ' ');
	paths = get_env_path_line(env);
	while (paths && paths[i])
	{
		paths[i] = join_free(paths[i], commands[0]);
		if (access(paths[i], X_OK) == 0)
		{
			ret = 0;
			break ;
		}
		++i;
	}
	free_split(commands);
	free_split(paths);
	return (ret);
}

int	exec(char **command, char **env)
{
	int		i;
	char	**paths;

	i = 0;
	// command = handle_quotes(command);
	paths = get_env_path_line(env);
	while (paths && paths[i])
	{
		paths[i] = join_free(paths[i], command[0]);
		if (paths[i])
			execve(paths[i], command, env);
		++i;
	}
	free_split(paths);
	return (-1);
}