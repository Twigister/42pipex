#include "bonus.h"
#include "../pipex.h"
#include <stdlib.h>

void	bonus_exec(char *cmd, t_pipex *data, char **env)
{
	char	**command;

	command = parse_command(cmd);
	if (!command)
		clean_exit(PARSE_FAIL, data);
	exec(command, env);
	free(command);
	exit(0);
}