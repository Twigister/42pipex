/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:14:32 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/26 18:14:33 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../pipex.h"

int	print_err_and_exit(char *s)
{
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	free(s);
	return (-1);
}
