/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file_access.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:00:28 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/26 18:00:29 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <unistd.h>

static int	test_file_access(char *path)
{
	if (access(path, F_OK) == -1)
	{
		print_err_and_exit(ft_strjoin(READ_NOT_EXIST, path));
		return (INVALID_INFILE);
	}
	else if (access(path, R_OK) == -1)
	{
		print_err_and_exit(ft_strjoin(NO_PERM, path));
		return (INVALID_INFILE);
	}
	return (0);
}

int	test_files_access(char **av, char **env)
{
	int	ret;

	ret = test_file_access(av[1]);
	if (ret)
		;
	else if (test_bin_access(av[2], env))
	{
		print_err_and_exit(ft_strjoin(EXEC_ERROR, av[2]));
		ret = ret | INVALID_PROGRAM_1;
	}
	else if (test_bin_access(av[3], env))
	{
		print_err_and_exit(ft_strjoin(EXEC_ERROR, av[3]));
		ret = ret | INVALID_PROGRAM_2;
	}
	else if (access(av[4], W_OK) == -1 && access(av[4], F_OK) == 0)
	{
		print_err_and_exit(ft_strjoin(NO_PERM, av[4]));
		ret = ret | INVALID_OUTFILE;
	}
	return (ret);
}
