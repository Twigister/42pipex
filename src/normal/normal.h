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
	int	cmd1_valid;
	int	cmd2_valid;
	int	pipefd[2];
	int	process;
}	t_pipex;

#endif
