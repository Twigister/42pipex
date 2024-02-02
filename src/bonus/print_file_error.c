#include <stdio.h>
#include <unistd.h>

void	print_file_error(const char *filename)
{
	write(2, "pipex: ", 7);
	perror(filename);
}
