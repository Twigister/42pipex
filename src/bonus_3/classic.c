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
		clean_exit(FORK_FAIL_FIRST, data);
	if (pid == 0)
	{
		close(data->pipefd[0]);
		if (fd == -1)
			clean_exit(INVALID_FD_IN, data);
		if (dup2(data->pipefd[1], 1) == -1)
			clean_exit(PIPE_DUP_FAIL_IN, data);
		if (dup2(fd, 0) == -1)
			clean_exit(PIPE_DUP_FAIL_IN, data);
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
		clean_exit(INTER_FORK, data);
	if (pid == 0)
	{
		close(data->pipefd[0]);
		if (dup2(data->pipefd[1], 1) == -1)
			clean_exit(INTER_DUP, data);
		if (dup2(data->read_fd, 0) == -1)
			clean_exit(INTER_DUP, data);
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
		clean_exit(OUT_FORK, data);
	if (pid == 0)
	{
		if (fd == -1)
			clean_exit(OUTFILE_ERR, data);
		else if (dup2(fd, 1) == -1)
			clean_exit(OUT_DUP_1, data);
		else if (dup2(data->read_fd, 0) == -1)
			clean_exit(OUT_DUP_2, data);
		close(fd);
		close(data->read_fd);
		bonus_exec(cmd, data, env);
	}
	close(data->read_fd);
}

void	pipex_classic(t_pipex *data, int ac, char **av, char **env)
{
	int	fd;
	int	i;

	i = 3;
	if (ac < 5)
		clean_exit(USAGE, data);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		clean_exit(INFILE_ERR, data);
	run_first(data, fd, av[2], env);
	init_pipes(data, fd);
	while (i < ac - 2)
	{
		if (pipe(data->pipefd) == -1)
			clean_exit(INTER_PIPE_FAIL, data);
		inter_run(data, av[i], env);
		swap_pipe(data);
		++i;
	}
	fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 00644);
	last_run(data, fd, av[ac - 2], env);
}