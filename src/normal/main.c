/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:22:43 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/29 15:46:42 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int	test_files_access(char **av, char **env);

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

void	main_iac(int pipefd[2], char **av, char **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, FORK_FAILED, ft_strlen(FORK_FAILED));
		exit(-1);
	}
	if (pid == 0)
		child(av, pipefd, env);
	close(pipefd[1]);
	pid = fork();
	if (pid == -1)
	{
		write(2, FORK_FAILED, ft_strlen(FORK_FAILED));
		wait(0);
		exit(-1);
	}
	if (pid == 0)
		parent(av, pipefd, env);
	close(pipefd[0]);
	wait(0);
	wait(0);
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	int	pipefd[2];

	if (ac != 5)
	{
		write(2, USAGE_MSG, ft_strlen(USAGE_MSG));
		return (0);
	}
	if (pipe(pipefd))
		return (print_err_and_exit(PIPE_FAILED));
	test_files_access(av, env);
	main_iac(pipefd, av, env);
}
