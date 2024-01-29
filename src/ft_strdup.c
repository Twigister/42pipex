/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:42:06 by arlarzil          #+#    #+#             */
/*   Updated: 2023/11/07 20:32:50 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	char	*res;

	i = 0;
	res = dest;
	while (*src && i < n)
	{
		*dest = *src;
		++i;
		++src;
		++dest;
	}
	while (i < n)
	{
		*dest = 0;
		++dest;
		++i;
	}
	return (res);
}

char	*ft_strndup_e(const char *s, size_t n)
{
	char	*res;

	if (!s)
		return (NULL);
	if (n <= 0)
		n = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	ft_strncpy(res, s, n);
	res[n] = 0;
	return (res);
}

char	*ft_strdup(const char *s)
{
	char	*res;
	char	*ptr;

	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	ptr = res;
	while (*s)
	{
		*ptr = *s;
		++ptr;
		++s;
	}
	*ptr = 0;
	return (res);
}
