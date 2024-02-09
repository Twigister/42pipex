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

static void	cmd1(t_pipex *data, const char *filename, char *cmd, char **env)
{
	char	**command;
	int		pid;

	command = parse_command(cmd);
	data->fd_in = open(filename, O_RDONLY);
	if (data->fd_in == -1)
	{
		write(2, "pipex: ", ft_strlen("pipex: "));
		perror(filename);
		return ;
	}
	pid = handle_fork();
	if (pid == 0)
	{
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

static void	cmd2(t_pipex *data, const char *file, char *cmd, char **env)
{
	char	**command;
	int		pid;

	data->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (data->fd_out == -1)
	{
		write(2, "pipex: ", ft_strlen("pipex: "));
		perror(file);
		return ;
	}
	command = parse_command(cmd);
	pid = handle_fork();
	if (pid == 0)
	{
		dup2(data->pipefd[0], 0);
		dup2(data->fd_out, 1);
		close(data->pipefd[1]);
		close(data->fd_out);
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

	init(&data, ac);
	cmd1(&data, av[1], av[2], env);
	if (data.fd_in != -1)
		close(data.fd_in);
	cmd2(&data, av[4], av[3], env);
	close(data.pipefd[0]);
	close(data.pipefd[1]);
	if (data.fd_out != -1)
		close(data.fd_out);
	while (data.process--)
		wait(0);
}
