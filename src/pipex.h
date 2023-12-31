/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:22:03 by arlarzil          #+#    #+#             */
/*   Updated: 2024/01/08 14:22:04 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define USAGE_MSG "Usage: ./pipex infile cmd1 cmd2 outfile\n"
# define FORK_FAILED "Error: The fork function failed\n"
# define EXEC_ERROR "pipex: command not found: "
# define PIPE_FAILED "The pipe function failed\n"
# include <stddef.h>

char	**ft_split(char *s, char c);
char	**free_split(char **p);

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strstr(const char *s, const char *b);
char	*ft_strdup(const char *s);
char	*join_free(char *s1, char *s2);
int		exec(char **command, char **env);
char	**get_env_path_line(char **env);
int		test_bin_access(char *command, char **env);
char	get_first_quote_type(char *s);
int		count_chars(char *s, char c);
char	**parse_command(char *s);

#endif
