#ifndef BONUS_H
# define BONUS_H

enum e_errcodes {
	USAGE = 0,
	INFILE_ERR,
	INIT_DUP_ERR,
	SWAP_DUP_ERR,
	OUTFILE_ERR,
	MAIN_PIPE_FAILED,
	INTER_PIPE_FAIL,
	FORK_FAIL_FIRST,
	INVALID_FD_IN,
	PIPE_DUP_FAIL_IN,
	PARSE_FAIL,
	INTER_FORK,
	INTER_DUP,
	OUT_FORK,
	OUT_DUP_1,
	OUT_DUP_2
};

# define USAGE_MSG_BONUS "Usage: ./pipex (here_doc) infile cmd1 [...] cmdn outfile\n"

typedef struct s_pipex {
	int		prog_count;
	int		pipefd[2];
	int		read_fd;
	int		heredoc;
}	t_pipex;

void	clean_exit(int err_code, t_pipex *data);

void	init_pipes(t_pipex *data, int fd);
void	swap_pipe(t_pipex *data);

void	pipex_classic(t_pipex *data, int ac, char **av, char **env);
void	pipex_heredoc(t_pipex *data, int ac, char **av, char **env);

void	bonus_exec(char *cmd, t_pipex *data, char **env);

#endif
