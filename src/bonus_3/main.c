#include "bonus.h"
#include "../pipex.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

static void	init_struct(t_pipex *data, const char *av1)
{
	if (av1)
		data->heredoc = !ft_strcmp(av1, "here_doc");
	else
		clean_exit(USAGE, data);
	data->prog_count = 0;
	if (pipe(data->pipefd) == -1)
		clean_exit(MAIN_PIPE_FAILED, data);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	data;
	if (ac > 2)
		init_struct(&data, av[1]);
	else
		init_struct(&data, NULL);
	if (data.heredoc)
		pipex_heredoc(&data, ac, av, env);
	else
		pipex_classic(&data, ac, av, env);
	while (data.prog_count--)
		wait(0);
}
