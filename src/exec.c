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

#include <stdlib.h>
#include <unistd.h>
#include "pipex.h"

int	test_bin_access(const char *command, char **env)
{
	char	**commands;
	int		ret;
	char	**paths;
	int		i;

	ret = -1;
	i = 0;
	commands = parse_command(ft_strdup(command));
	if (!commands)
		return (-1);
	paths = get_env_path_line(env);
	if (count_chars(commands[0], '/') && access(commands[0], X_OK) == 0)
		ret = 0;
	while (paths && paths[i] && ret == -1)
	{
		paths[i] = join_free(paths[i], commands[0]);
		if (access(paths[i], X_OK) == 0)
			ret = 0;
		++i;
	}
	return (free(*commands), free(commands), free_split(paths), ret);
}

static void	no_command(char **command)
{
	free(command);
	write(2, "pipex: no command\n", 19);
	exit(0);
}

int	exec(char **command, char **env)
{
	int		i;
	char	**paths;

	if (!command)
		exit(1);
	if (!command[0])
		no_command(command);
	i = 0;
	paths = get_env_path_line(env);
	if (count_chars(command[0], '/'))
		execve(command[0], command, env);
	while (paths && paths[i])
	{
		paths[i] = join_free(paths[i], command[0]);
		if (paths[i])
			execve(paths[i], command, env);
		++i;
	}
	free_split(paths);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	exit (1);
}
