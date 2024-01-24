#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "bonus.h"
#include "../pipex.h"

void	clean_exit(int err, t_pipex *data)
{
	//const char	*msg[] = {}; // TBD

	(void)data;
	if (err == USAGE)
		write(2, USAGE_MSG_BONUS, ft_strlen(USAGE_MSG_BONUS));
	else
		perror("pipex");
	exit(err);
}
