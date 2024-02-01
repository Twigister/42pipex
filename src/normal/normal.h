#ifndef _NORMAL_H
# define NORMAL_H

typedef struct s_pipex
{
	int	fd_in;
	int	fd_out;
	int	cmd1_valid;
	int	cmd2_valid;
	int	pipefd[2];
	int	process;
}	t_pipex;

#endif