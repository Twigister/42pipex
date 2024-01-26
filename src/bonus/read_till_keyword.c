/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_till_keyword.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:58:25 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/26 17:01:51 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "bonus.h"
#include "../pipex.h"
#include <unistd.h>
#include <stdlib.h>

void	read_till_keyword(int fd, const char *word)
{
	char	*line;
	int		word_len;

	line = get_next_line(0);
	word_len = ft_strlen(word);
	while (line)
	{
		if (ft_strncmp(line, word, word_len) == 0
			&& (line[word_len] == '\n' || line[word_len] == '\0'))
			break ;
		else
			write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
}
