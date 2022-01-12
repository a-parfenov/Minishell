
#include "minishell.h"

void	exe(t_obj *o)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		printf("error\n");
	}
	else if (pid > 0)
	{
		wait(&status);
		printf("status is %d\n", status);
	}
	else
	{
		char *arg[3] = {"pwd", "-L", NULL};
		execve("/bin/pwd", arg, o->env);
		perror(ERROR_NAME);
		exit(127);
	}
}
