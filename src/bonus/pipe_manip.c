/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_manip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:58:00 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/26 16:58:01 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include <unistd.h>

void	init_pipes(t_pipex *data, int fd)
{
	data->read_fd = dup(data->pipefd[0]);
	if (data->read_fd < 0)
		clean_exit(INIT_DUP_ERR, data, NULL);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	close(fd);
}

void	swap_pipe(t_pipex *data)
{
	close(data->pipefd[1]);
	close(data->read_fd);
	data->read_fd = dup(data->pipefd[0]);
	if (data->read_fd < 0)
		clean_exit(SWAP_DUP_ERR, data, NULL);
	close(data->pipefd[0]);
}
