/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:27:05 by arlarzil          #+#    #+#             */
/*   Updated: 2024/02/01 14:27:07 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMAL_H
# define NORMAL_H

typedef struct s_pipex
{
	int	fd_in;
	int	fd_out;
	int	pipefd[2];
	int	process;
	int	prog1exists;
	int	prog2exists;
}	t_pipex;

void	open_files(t_pipex *data, const char *in, const char *out);
void	test_bins(t_pipex *data, const char *c1, const char *c2, char **env);

#endif
