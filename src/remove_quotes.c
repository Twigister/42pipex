/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:55:36 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/12 17:55:37 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	remove_quotes(char *s)
{
	int		i;
	int		step;
	char	quote;

	quote = 0;
	i = 0;
	step = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '\'' || s[i] == '"'))
		{
			quote = s[i];
			step += 1;
		}
		else if (quote && s[i] == quote)
		{
			++step;
			quote = 0;
		}
		else
			s[i - step] = s[i];
		++i;
	}
	s[i - step] = 0;
}
