#include "../pipex.h"

#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	**get_env_path_line(char **env)
{
	int		i;
	char	**res;


	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH=") == env[i])
		{
			res = ft_split(env[i] + ft_strlen("PATH="), ':');
			break ;
		}
		++i;
	}
	i = 0;
	while (res && res[i])
	{
		res[i] = join_free(res[i], "/");
		if (!res[i])
		{
			free_split(res);
			break ;
		}
		++i;
	}
	return (res);
}

int	exec(char **command, char **env)
{
	int		i;
	char	**paths;

	i = 0;
	paths = get_env_path_line(env);
	while (paths && paths[i])
	{
		paths[i] = join_free(paths[i], command[0]);
		if (paths[i] && execve(paths[i], command, env) != -1)
			break ;
		++i;
	}
	free_split(paths);
	return (0);
}

// Le parent lit du 1er fichier et écrit dans le pipe
void	parent(char **av, int pipefd[2], char **env)
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

void	child(char **av, int pipefd[2], char **env)
{
	(void)env;
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

	if (pipe(pipefd))
		return (-1);
	if (ac != 5)
	{
		write(2, USAGE_MSG, ft_strlen(USAGE_MSG));
		return (0);
	}
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
	return (0);
}
