/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:14:15 by arlarzil          #+#    #+#             */
/*   Updated: 2023/11/21 15:28:38 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static char	*ft_cat_n(char *s1, int *s1_len, char *s2, int n)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(*s1_len + n + 1);
	if (res)
	{
		while (s1[i])
		{
			res[i] = s1[i];
			++i;
		}
		while (j < n)
		{
			res[i + j] = s2[j];
			++j;
		}
		res[i + j] = '\0';
	}
	free(s1);
	return (res);
}

int	find_next_end(t_string *res, char *buf, int *i, int last_read)
{
	int	len;

	len = 0;
	while ((*i + len) < last_read && buf[*i + len] != '\n')
		++len;
	if ((*i + len) < last_read && buf[*i + len] == '\n')
		++len;
	if (!res->s)
	{
		res->s = malloc(1);
		if (!res->s)
			return (0);
		res->s[0] = 0;
	}
	res->s = ft_cat_n(res->s, &(res->len), buf + *i, len);
	*i += len;
	res->len += len;
	if (buf[*i - 1] == '\n' || !res->s)
		return (0);
	return (1);
}

static int	get_next_line_step(t_gnl *cur, t_string *s, int fd)
{
	if (cur->i > cur->last_read_size)
	{
		cur->i = 0;
		cur->last_read_size = 0;
		return (1);
	}
	if (cur->i == cur->last_read_size)
	{
		cur->last_read_size = read(fd, &(cur->buf), BUFFER_SIZE);
		if (cur->last_read_size == -1)
		{
			free(s->s);
			s->s = NULL;
			return (1);
		}
		cur->i = 0;
		if (cur->last_read_size < BUFFER_SIZE)
			cur->buf[cur->last_read_size] = 0;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_gnl	data;	
	t_string		s;
	int				flag;

	s.s = NULL;
	s.len = 0;
	flag = 1;
	while (flag)
	{
		if (get_next_line_step(&data, &s, fd) == 1)
			return (s.s);
		if (data.last_read_size == 0)
			return (s.s);
		flag = find_next_end(&s, data.buf, &(data.i), data.last_read_size);
	}
	return (s.s);
}
