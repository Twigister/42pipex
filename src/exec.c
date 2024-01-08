/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:21:42 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/08 14:21:42 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"

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
