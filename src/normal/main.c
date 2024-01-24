/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:22:43 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/08 14:22:43 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

static void	child(char **av, int pipefd[2], char **env)
{
	char	**command;
	int		fd;
	int		ret;

	ret = 0;
	fd = open(av[1], O_RDONLY);
	close(pipefd[0]);
	if (fd == -1)
		ret = 1;
	command = parse_command(av[2]);
	if (fd != -1 && command)
	{
		dup2(pipefd[1], 1);
		dup2(fd, 0);
		close(fd);
		close(pipefd[1]);
		exec(command, env);
	}
	close(fd);
	free(command);
	close(pipefd[1]);
	exit(ret);
}

static void	parent(char **av, int pipefd[2], char **env)
{
	int		fd;
	char	**command;
	int		ret;

	ret = 0;
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 00664);
	close(pipefd[1]);
	if (fd == -1)
		ret = 1;
	command = parse_command(av[3]);
	if (fd != -1 && command)
	{
		dup2(pipefd[0], 0);
		dup2(fd, 1);
		close(fd);
		close(pipefd[0]);
		exec(command, env);
	}
	close(fd);
	free(command);
	close(pipefd[0]);
	exit(ret);
}

static int	print_err_and_exit(char *s)
{
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	free(s);
	return (-1);
}

static int	test_file_access(char *path)
{
	if (access(path, F_OK) == -1)
	{
		print_err_and_exit(ft_strjoin(READ_NOT_EXIST, path));
		return (INVALID_INFILE);
	}
	else if (access(path, R_OK) == -1)
	{
		print_err_and_exit(ft_strjoin(NO_PERM, path));
		return (INVALID_INFILE);
	}
	return (0);
}

static int	test_files_access(char **av, char **env)
{
	int	ret;

	ret = test_file_access(av[1]);
	if (ret)
		;
	else if (test_bin_access(av[2], env))
	{
		print_err_and_exit(ft_strjoin(EXEC_ERROR, av[2]));
		ret = ret | INVALID_PROGRAM_1;
	}
	else if (test_bin_access(av[3], env))
	{
		print_err_and_exit(ft_strjoin(EXEC_ERROR, av[3]));
		ret = ret | INVALID_PROGRAM_2;
	}
	else if (access(av[4], W_OK) == -1 && access(av[4], F_OK) == 0)
	{
		print_err_and_exit(ft_strjoin(NO_PERM, av[4]));
		ret = ret | INVALID_OUTFILE;
	}
	return (ret);
}

int	main(int ac, char **av, char **env)
{
	int	pipefd[2];
	int	pid;

	if (ac != 5)
	{
		write(2, USAGE_MSG, ft_strlen(USAGE_MSG));
		return (0);
	}
	if (pipe(pipefd))
		return (print_err_and_exit(PIPE_FAILED));
	test_files_access(av, env);
	pid = fork();
	if (pid == -1)
	{
		write(2, FORK_FAILED, ft_strlen(FORK_FAILED));
		return (-1);
	}
	if (pid == 0)
		child(av, pipefd, env);
	close(pipefd[1]);
	pid = fork();
	if (pid == -1)
	{
		write(2, FORK_FAILED, ft_strlen(FORK_FAILED));
		return (-1);
	}
	if (pid == 0)
		parent(av, pipefd, env);
	close(pipefd[0]);
	wait(0);
	wait(0);
	//write(1, "Coucou\n", 7);
}
