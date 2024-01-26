/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:15:05 by arlarzil          #+#    #+#             */
/*   Updated: 2023/11/21 15:49:38 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl {
	char			buf[BUFFER_SIZE];
	int				last_read_size;
	int				i;
}	t_gnl;

typedef struct s_string {
	char	*s;
	int		len;
}	t_string;

t_gnl	*get_node(t_gnl *descs, int fd);
t_gnl	*add_fd(t_gnl **descs, int fd);
t_gnl	**get_descs(void);

int		find_next_end(t_string *res, char *buf, int *i, int last_read);

char	*get_next_line(int fd);

#endif
