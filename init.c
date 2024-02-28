#include "main.h"

/**
 * local_init - initializes all the local Data Structure
 * @ac: main function argc
 * @av: main function argv
 * @envp: main funtion environ
 *
 * Return: local data structure
 */
local_t *local_init(int ac, char **av, char **envp)
{
	char *prompt = "$ ";
	local_t *local = NULL;

	local = (local_t *) malloc(sizeof(local_t));
	if (local == NULL)
		return (NULL);

	local->prompt = prompt;

	local->fd = STDIN_FILENO;
	if (ac == 2)
		local->fd = open(av[1], O_RDONLY);
	local->error_checker = 0;
	local->exit_status = 0;

	local->ac = ac;
	local->av = av;

	local->argv = NULL;
	local->environ = envp;

	local->active = 1;
	if (!isatty(STDIN_FILENO) || ac == 2)
		local->active = 0;
	signal(SIGINT, int_handler);
	local->signal = 0;


	return (local);
}

/**
 * int_handler - CTRL C
 * @sig: signal
 */
void int_handler(int sig)
{
	char *prompt = "$ ";

	signal(sig, SIG_IGN);
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, &prompt[0], 2);
	errno = 130;
	signal(SIGINT, int_handler);
}

