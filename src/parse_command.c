/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:19:43 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/11 15:19:43 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

static int	get_quote_len(char *command, char quote)
{
	int	i;

	i = 0;
	while (command[i] != quote)
	{
		if (!command[i])
			return (-1);
		++i;
	}
	return (i - 1);
}

static int	skip_word(char *base)
{
	int		len;
	char	*cmd;

	cmd = base;
	while (*cmd && !ft_isspace(*cmd))
	{
		if (*cmd == '"' || *cmd == '\'')
		{
			len = get_quote_len(cmd + 1, *cmd);
			if (len != -1)
				cmd += len + 3;
			else
				return (-1);
		}
		else
			while (*cmd && !ft_isspace(*cmd) && !(*cmd == '"' || *cmd == '\''))
				++cmd;
	}
	return (cmd - base);
}

static int	count_words(char *command)
{
	int		res;
	int		len;

	res = 0;
	while (*command)
	{
		while (ft_isspace(*command))
			++command;
		if (*command)
			res += 1;
		len = skip_word(command);
		if (len == -1)
			return (-1);
		command += len;
	}
	return (res);
}

static char	**fill_tab(char *command, char **tab, int word_count)
{
	int	i;

	i = 0;
	while (i < word_count)
	{
		while (ft_isspace(*command))
			++command;
		tab[i] = command;
		while (*command && !ft_isspace(*command))
		{
			if (*command == '"' || *command == '\'')
				command += get_quote_len(command + 1, *command) + 3;
			else
				while (*command && !ft_isspace(*command) && \
				!(*command == '"' || *command == '\''))
					++command;
		}
		if (*command != 0)
			*(command++) = 0;
		remove_quotes(tab[i]);
		++i;
	}
	tab[i] = NULL;
	return (tab);
}

char	**parse_command(char *command)
{
	char	**res;
	int		word_count;

	if (command == NULL)
		return (NULL);
	word_count = count_words(command);
	if (word_count == -1)
		return (NULL);
	res = malloc(sizeof(char *) * (word_count + 1));
	if (!res)
		return (NULL);
	return (fill_tab(command, res, word_count));
}
