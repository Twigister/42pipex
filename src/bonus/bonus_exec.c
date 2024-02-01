/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:55:10 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/26 16:55:13 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "../pipex.h"
#include <stdlib.h>

void	bonus_exec(char *cmd, t_pipex *data, char **env)
{
	char	**command;

	command = parse_command(cmd);
	if (!command)
		clean_exit(PARSE_FAIL, data, cmd);
	exec(command, env);
	free(command);
	exit(0);
}
