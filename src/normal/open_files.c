/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:08:25 by arlarzil          #+#    #+#             */
/*   Updated: 2024/02/12 16:08:25 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normal.h"
#include "../pipex.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

void	open_files(t_pipex *data, const char *in, const char *out)
{
	data->fd_out = open(out, O_CREAT | O_TRUNC | O_WRONLY, 00644);
	if (data->fd_out == -1)
	{
		write(2, "pipex: ", ft_strlen("pipex: "));
		perror(out);
	}
	data->fd_in = open(in, O_RDONLY);
	if (data->fd_in == -1)
	{
		write(2, "pipex: ", ft_strlen("pipex: "));
		perror(in);
	}
}

static void	write_prog_name(const char *s)
{
	int	len;

	len = 0;
	while (s[len] > 32)
		++len;
	write(2, s, len);
}

void	test_bins(t_pipex *data, const char *c1, const char *c2, char **env)
{
	data->prog1exists = !test_bin_access(c1, env);
	if (!data->prog1exists && data->fd_in)
	{
		write(2, "pipex: ", 8);
		write_prog_name(c1);
		write(2, ": command not found\n", 21);
	}
	data->prog2exists = !test_bin_access(c2, env);
	if (!data->prog2exists && data->fd_out)
	{
		write(2, "pipex: ", 8);
		write_prog_name(c2);
		write(2, ": command not found\n", 21);
	}
}
