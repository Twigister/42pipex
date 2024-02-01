/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:56:14 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/26 16:56:15 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "bonus.h"
#include "../pipex.h"

void	clean_exit(int err, t_pipex *data, const char *string)
{
	(void)data;
	if (err == USAGE)
		write(2, USAGE_MSG_BONUS, ft_strlen(USAGE_MSG_BONUS));
	else
	{
		if (string)
		{
			write(2, "pipex: ", ft_strlen("pipex: "));
			perror(string);
		}
		else
			perror("pipex");
	}
	exit(err);
}
