/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:30:07 by arlarzil          #+#    #+#             */
/*   Updated: 2023/11/06 14:43:28 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s);

char	*ft_strcpy(char *dest, const char *src)
{
	char	*res;

	res = dest;
	while (*src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = 0;
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		len_s1;

	len_s1 = ft_strlen(s1);
	res = malloc(sizeof(char) * (len_s1 + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	ft_strcpy(&ft_strcpy(res, s1)[len_s1], s2);
	return (res);
}

char	*join_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}
