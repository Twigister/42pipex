/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:43:41 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/08 15:43:42 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

static char	**free_shit(char **tab, char **tab_end)
{
	int	i;

	i = 0;
	while (tab_end[i])
	{
		free(tab_end[i]);
		++i;
	}
	free_split(tab);
	return (NULL);
}

static char	**concat_chunks(char **tab)
{
	int		pos_write;
	int		pos_read;
	char	quote_type;
	char	*tmp;

	pos_write = 0;
	pos_read = 0;
	while (tab[pos_read])
	{
		quote_type = get_first_quote_type(tab[pos_read]);
		while (quote_type && (tab[pos_read], quote_type) % 2 == 0)
		{
			tmp = tab[pos_write];
			tab[pos_write] = ft_strjoin(tab[pos_write], tab[pos_read]);
			if (!tab)
				return (free_shit(tab, tab + pos_read));
			free(tmp);
			free(tab[pos_read]);
			tab[pos_read] = NULL;
			++pos_read;
		}
		++pos_write;
		++pos_read;
	}
	return (tab);
}

static void	remove_word_quotes(char *w)
{
	int		i;
	int		step;
	char	last_quote;

	last_quote = 0;
	step = 0;
	i = 0;
	while (w[i])
	{
		if (last_quote == 0 && (w[i] == '"' || w[i] == '\''))
		{
			last_quote = w[i];
			step += 1;
		}
		else if (last_quote == w[i])
		{
			step += 1;
			last_quote = 0;
		}
		else
			w[i - step] = w[i];
		++i;
	}
	w[i - step] = 0;
}

static char	**remove_quotes(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		remove_word_quotes(tab[i]);
		++i;
	}
	return (tab);
}

char	**parse_command(char *c)
{
	char	**res;

	res = ft_split(c, ' ');
	if (!res)
		return (NULL);
	return (remove_quotes(concat_chunks(res)));
}

#include <stdio.h>
int	main(int ac, char **av)
{
	int	i = 0;
	char	**tab = parse_command(av[ac -1]);

	while (tab[i])
	{
		printf("%s: ", tab[i]);
		remove_word_quotes(tab[i]);
		printf("%s\n", tab[i]);
		++i;
	}
	free_split(tab);
}
