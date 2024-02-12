/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:26:45 by arlarzil          #+#    #+#             */
/*   Updated: 2024/02/01 14:26:48 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normal.h"
#include "../pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static int	handle_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("pipex");
		exit(1);
	}
	return (pid);
}

static void	cmd1(t_pipex *data, char *cmd, char **env)
{
	char	**command;
	int		pid;

	if (data->fd_in == -1)
		return ;
	if (!data->prog1exists)
		return ;
	command = parse_command(cmd);
	pid = handle_fork();
	if (pid == 0)
	{
		if (data->fd_out != -1)
			close(data->fd_out);
		dup2(data->fd_in, 0);
		dup2(data->pipefd[1], 1);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		close(data->fd_in);
		exec(command, env);
	}
	free(command);
	++data->process;
}

static void	cmd2(t_pipex *data, char *cmd, char **env)
{
	char	**command;
	int		pid;

	if (data->fd_out == -1)
		return ;
	if (!data->prog2exists)
		return ;
	command = parse_command(cmd);
	pid = handle_fork();
	if (pid == 0)
	{
		if (data->prog1exists)
			dup2(data->pipefd[0], 0);
		else
			close(0);
		dup2(data->fd_out, 1);
		close(data->pipefd[1]);
		close(data->fd_out);
		close(data->pipefd[0]);
		exec(command, env);
	}
	free(command);
	++data->process;
}

static void	init(t_pipex *data, int ac)
{
	if (ac != 5)
	{
		write(2, USAGE_MSG, ft_strlen(USAGE_MSG));
		exit(1);
	}
	if (pipe(data->pipefd))
	{
		write(2, PIPE_FAILED, ft_strlen(PIPE_FAILED));
		exit(1);
	}
	data->process = 0;
}

int	main(int ac, char **av, char **env)
{
	t_pipex	data;
	int		ret;

	init(&data, ac);
	open_files(&data, av[1], av[4]);
	test_bins(&data, av[2], av[3], env);
	cmd1(&data, av[2], env);
	if (data.fd_in != -1)
		close(data.fd_in);
	cmd2(&data, av[3], env);
	close(data.pipefd[0]);
	close(data.pipefd[1]);
	if (data.fd_out != -1)
		close(data.fd_out);
	while (data.process--)
		waitpid(-1, &ret, 0);
	if (!data.prog2exists)
		return (127);
	ret = WEXITSTATUS(ret);
	return (ret);
}
