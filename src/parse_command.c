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
		while (*command && !ft_isspace(*command))
		{
			if (*command == '"' || *command == '\'')
			{
				len = get_quote_len(command + 1, *command);
				if (len != -1)
					command += len + 3;
				else
					return (-1);			
			}
			else
				while (*command && !ft_isspace(*command) && !(*command == '"' || *command == '\''))
					++command;
		}
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
				while (*command && !ft_isspace(*command) && !(*command == '"' || *command == '\''))
					++command;	
		}
		if (*command != 0)
			*(command++) = 0;
		++i;
	}
	tab[i] = NULL;
	return (tab);
}

char	**parse_command(char *command)
{
	char	**res;
	int		word_count;

	word_count = count_words(command);
	if (word_count == -1)
		return (NULL);
	res = malloc(sizeof(char *) * (word_count + 1));
	if (!res)
		return (NULL);
	return (fill_tab(command, res, word_count));
}
/*
#include <stdio.h>
int	main(int ac, char **av)
{
	int	i = 0;
	int	j;
	char	**command;

	while (i < ac)
	{
		j = 0;
		command = parse_command(av[i]);
		printf("Command: %s:", av[i]);
		while (command[j])
		{
			printf("command[%d]: %s ", j, command[j]);
			++j;
		}
		printf("\n");
		++i;
	}
}*/