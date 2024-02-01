#include "normal.h"
#include "../pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

static void	cmd1(t_pipex *data, const char *filename, char *cmd, char **env)
{
	char	**command;
	int		pid;

	data->fd_in = open(filename, O_RDONLY);
	if (data->fd_in == -1)
	{
		write(2, "pipex: ", ft_strlen("pipex: "));
		perror(filename);
		return ;
	}
	command = parse_command(cmd);
	pid = fork();
	if (pid == -1)
	{
		write(2, FORK_FAILED, ft_strlen(FORK_FAILED));
		exit(1);
	}
	else if (pid == 0)
	{
		dup2(data->fd_in, 0);
		dup2(data->pipefd[1], 1);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		close(0);
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
	pid = fork();
	if (pid == -1)
	{
		write(2, FORK_FAILED, ft_strlen(FORK_FAILED));
		exit(1);
	}
	else if (pid == 0)
	{
		dup2(data->pipefd[0], 0);
		dup2(data->fd_out, 1);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		close(data->fd_out);
		exec(command, env);
	}
	free(command);
	++data->process;
}

int	main(int ac, char **av, char **env)
{
	t_pipex	data;

	data.process = 0;
	if (ac != 5)
	{
		write(2, USAGE_MSG, ft_strlen(USAGE_MSG));
		return (1);
	}
	if (pipe(data.pipefd))
	{
		write(2, PIPE_FAILED, ft_strlen(PIPE_FAILED));
		return (1);
	}
	cmd1(&data, av[1], av[2], env);
	if (data.fd_in != -1)
		close(data.fd_in);
	close(data.pipefd[1]);
	cmd2(&data, av[4], av[3], env);
	close(data.pipefd[0]);
	if (data.fd_out != -1)
		close(data.fd_out);
	close(0);
	close(1);
	close(2);
	while (data.process--)
		wait(0);
}
