/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:02:06 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/12 16:02:06 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
static void	parent(char **av, int pipefd[2], char **env)
{
	char	**command;
	int		fd;

	fd = open(av[1], O_RDONLY);
	command = ft_split(av[2], ' ');
	close(pipefd[0]);
	if (fd != -1 && command)
	{
		dup2(pipefd[1], 1);
		dup2(fd, 0);
		exec(command, env);
	}
	close(pipefd[1]);
	if (fd != -1)
		close(fd);
	free_split(command);
}

static int inter(char *command, char **env)
{
    char    **split_command;
    int     pipefd[2];
    int     pid;

    if (pipe)
        return (-1);
    pid = fork();
    if (pid == -1)
        return (-1);
    else if (!pid)
    {
        split_command = ft_split(command, ' ');
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        if (exec(split_command, env) == -1)
        {
            write(2, EXEC_ERROR, ft_strlen(EXEC_ERROR));
            write(2, split_command[])
    }
    else
    {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
    }
    return (0);
}

static void	child(char **av, int pipefd[2], char **env)
{
	int		fd;
	char	**command;

	fd = open(av[4], O_WRONLY | O_CREAT);
	command = ft_split(av[3], ' ');
	close(pipefd[1]);
	if (fd != -1 && command)
	{
		dup2(pipefd[0], 0);
		dup2(fd, 1);
		exec(command, env);
	}
	close(pipefd[0]);
	if (fd != -1)
		close(fd);
	free_split(command);
}

int	main(int ac, char **av, char **env)
{
	int	pipefd[2];
	int	pid;
    int i;

	if (pipe(pipefd))
		return (-1);
	if (ac < 5)
	{
		write(2, USAGE_MSG, ft_strlen(USAGE_MSG));
		return (0);
	}
    parent();
	return (0);
}*/
