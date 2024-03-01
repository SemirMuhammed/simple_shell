#include "main.h"

/**
 * main - print prompt, wait for user to enter command & print it on a newline
 * @ac: argument count
 * @av: array of arguments
 * @envp: array of environment variables
 *
 * Return: Always 0
 */
int main(int ac, char **av, char **envp)
{
	static int pc = 1;
	static local_t *local;
	int checker = 0;

	local = local_init(ac, av, envp);
	if (local == NULL)
		return (-1);
	while (1)
	{
		local->pc = pc;

		checker = handle_prompt(&local);
		if (checker == 2)
			continue;
		pc++;

		if (ac == 2)
			close(local->fd);
		fflush(stdin);
	}
	free(local);
	return (local->exit_status);
}

