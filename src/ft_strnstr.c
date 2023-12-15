/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:55:41 by arlarzil          #+#    #+#             */
/*   Updated: 2023/11/07 16:50:34 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2 || n == 0)
		return (0);
	while (*s1 && i + 1 < n)
	{
		if (*s1 != *s2)
			break ;
		++s1;
		++s2;
		++i;
	}
	return ((unsigned char)*s1 - (unsigned int)*s2);
}

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	len_l;

	i = 0;
	if (!*little)
		return ((char *)big);
	len_l = ft_strlen(little);
	while (big[i])
	{
		if (ft_strncmp(little, &big[i], len_l) == 0)
			return ((char *)&big[i]);
		++i;
	}
	return (NULL);
}
