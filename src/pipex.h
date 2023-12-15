#ifndef PIPEX_H
# define PIPEX_H

# define USAGE_MSG "Usage: ./pipex infile cmd1 cmd2 outfile\n"
# define FORK_FAILED "Error: The fork function failed\n"
# define EXEC_ERROR "pipex: command not found: "
# define PIPE_FAILED "The pipe function failed\n"
# include <stddef.h>

char    **ft_split(char *s, char c); // Faire un split qui prend un charset serait PE plus pertinent ici
char	**free_split(char **p);


size_t  ft_strlen(const char *s);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_strstr(const char *s, const char *b);
char    *ft_strdup(const char *s);
char	*join_free(char *s1, char *s2);
int 	exec(char **command, char **env);
char	**get_env_path_line(char **env);
int	test_bin_access(char *command, char **env);

#endif
