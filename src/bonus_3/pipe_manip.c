#include "bonus.h"
#include <unistd.h>

void	init_pipes(t_pipex *data, int fd)
{
	data->read_fd = dup(data->pipefd[0]);
	if (data->read_fd < 0)
		clean_exit(INIT_DUP_ERR, data);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	close(fd);
}

void	swap_pipe(t_pipex *data)
{
	close(data->pipefd[1]);
	close(data->read_fd);
	data->read_fd = dup(data->pipefd[0]);
	if (data->read_fd < 0)
		clean_exit(SWAP_DUP_ERR, data);
	close(data->pipefd[0]);
}
