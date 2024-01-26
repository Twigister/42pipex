/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:59:36 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/26 17:00:27 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <stddef.h>

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
	OUT_DUP_2,
	TEMP_FILE_ERR,
};

# define USAGE_MSG_BONUS "Usage: ./pipex (here_doc) \
	infile/limiter cmd1 [...] cmdn outfile\n"

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

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	read_till_keyword(int fd, const char *word);

#endif
