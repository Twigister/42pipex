/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:01:27 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/26 17:01:28 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

static void	run_first(t_pipex *data, int fd, char *cmd, char **env)
{
	int	pid;

	data->prog_count++;
	pid = fork();
	if (pid == -1)
		clean_exit(FORK_FAIL_FIRST, data, NULL);
	if (pid == 0)
	{
		close(data->pipefd[0]);
		if (fd == -1)
			clean_exit(INVALID_FD_IN, data, "temp file: in");
		if (dup2(data->pipefd[1], 1) == -1)
			clean_exit(PIPE_DUP_FAIL_IN, data, NULL);
		if (dup2(fd, 0) == -1)
			clean_exit(PIPE_DUP_FAIL_IN, data, NULL);
		close(fd);
		close(data->pipefd[1]);
		bonus_exec(cmd, data, env);
	}
}

static void	inter_run(t_pipex *data, char *cmd, char **env)
{
	int	pid;

	data->prog_count++;
	pid = fork();
	if (pid == -1)
		clean_exit(INTER_FORK, data, NULL);
	if (pid == 0)
	{
		close(data->pipefd[0]);
		if (dup2(data->pipefd[1], 1) == -1)
			clean_exit(INTER_DUP, data, NULL);
		if (dup2(data->read_fd, 0) == -1)
			clean_exit(INTER_DUP, data, NULL);
		close(data->read_fd);
		close(data->pipefd[1]);
		bonus_exec(cmd, data, env);
	}
}

static void	last_run(t_pipex *data, int fd, char *cmd, char **env)
{
	int	pid;

	data->prog_count++;
	pid = fork();
	if (pid == -1)
		clean_exit(OUT_FORK, data, NULL);
	if (pid == 0)
	{
		if (fd == -1)
			clean_exit(OUTFILE_ERR, data, "temp file: out");
		else if (dup2(fd, 1) == -1)
			clean_exit(OUT_DUP_1, data, NULL);
		else if (dup2(data->read_fd, 0) == -1)
			clean_exit(OUT_DUP_2, data, NULL);
		close(fd);
		close(data->read_fd);
		bonus_exec(cmd, data, env);
	}
	close(data->read_fd);
}

static int	gen_tmp_file(char *keyword)
{
	char	filename[17];
	int		j;
	char	fds[2];

	int (i) = 0;
	while (i < 16)
	{
		j = '0';
		while (j < '9')
		{
			filename[i] = j;
			filename[i + 1] = 0;
			fds[0] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00644);
			if (fds[0] != -1)
			{
				fds[1] = open(filename, O_RDONLY);
				unlink(filename);
				read_till_keyword(fds[0], keyword);
				return (fds[1]);
			}
			++j;
		}
		++i;
	}
	return (-1);
}

void	pipex_heredoc(t_pipex *data, int ac, char **av, char **env)
{
	int	fd;
	int	i;

	i = 4;
	if (ac < 6)
		clean_exit(USAGE, data, NULL);
	fd = gen_tmp_file(av[2]);
	if (fd == -1)
		clean_exit(TEMP_FILE_ERR, data, NULL);
	run_first(data, fd, av[3], env);
	init_pipes(data, fd);
	while (i < ac - 2)
	{
		if (pipe(data->pipefd) == -1)
			clean_exit(INTER_PIPE_FAIL, data, NULL);
		inter_run(data, av[i], env);
		swap_pipe(data);
		++i;
	}
	fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 00644);
	last_run(data, fd, av[ac - 2], env);
}
