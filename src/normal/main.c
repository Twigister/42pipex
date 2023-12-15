#include "../pipex.h"

#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
// Le child lit du 1er fichier et écrit dans le pipe
static void	child(char **av, int pipefd[2], char **env)
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

static void	parent(char **av, int pipefd[2], char **env)
{
	(void)env;
	int		fd;
	char	**command;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 00664);
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

int	print_err_and_exit(char *s)
{
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	free(s);
	return (-1);
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
	if (test_bin_access(av[2], env))
		return (print_err_and_exit(ft_strjoin(EXEC_ERROR, av[2])));
	if (test_bin_access(av[3], env))
		return (print_err_and_exit(ft_strjoin(EXEC_ERROR, av[3])));

	pid = fork();
	if (pid == -1)
	{
		write(2, FORK_FAILED, ft_strlen(FORK_FAILED));
		return (-1);
	}
	if (pid == 0)
		child(av, pipefd, env);
	else
		parent(av, pipefd, env);
}
