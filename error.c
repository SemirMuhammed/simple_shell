#include "main.h"

/**
 * error - print error
 * @local: data structure
 *
 * Return: errno
 */
int error(local_t **local)
{
	int status = 2;

	print_error_init(&(*local));
	if ((*local)->error_checker)
		handle_builtin_errors(&(*local));
	else
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, &((*local)->argv[0])[0], _strlen((*local)->argv[0]));
		if ((*local)->signal != 20)
			write(STDERR_FILENO, ": not found\n", 12);
		else
			write(STDERR_FILENO, ": File name too long\n", 21);
		status = 127;
	}
	if ((*local)->error_checker == 7)
		status = 127;

	return (status);
}

/**
 * print_error_init - prints filename and prompt count
 * @local: data structure
 */
void print_error_init(local_t **local)
{
	char *ec = NULL;

	write(STDERR_FILENO, &(*local)->av[0][0], _strlen((*local)->av[0]));
	write(STDERR_FILENO, ": ", 2);
	if ((*local)->ac == 2)
		ec = itoa(0);
	else
		ec = itoa((*local)->pc);
	write(STDERR_FILENO, &ec[0], _strlen(ec));
	free(ec);
}

/**
 * handle_builtin_errors - handles print of errors related to built-in commands
 * @local: data structure
 */
void handle_builtin_errors(local_t **local)
{
	char *temp = ": Syntax error: \"\" unexpected\n";

	if ((*local)->error_checker == 1)
	{
		write(STDERR_FILENO, ": exit: Illegal number: ", 24);
		write(STDERR_FILENO, &((*local)->argv[1])[0], _strlen((*local)->argv[1]));
		write(STDERR_FILENO, "\n", 1);
	}
	else if ((*local)->error_checker == 2)
		write(STDERR_FILENO, ": Usage: setenv VARIABLE VALUE\n", 31);
	else if ((*local)->error_checker == 3)
		write(STDERR_FILENO, ": Usage: unsetenv VARIABLE\n", 27);
	else if ((*local)->error_checker == 4)
	{
		write(STDERR_FILENO, ": cd: can't cd to ", 18);
		write(STDERR_FILENO, &((*local)->argv[1])[0], _strlen((*local)->argv[1]));
		write(STDERR_FILENO, "\n", 1);
	}
	else if ((*local)->error_checker == 5)
	{
		write(STDERR_FILENO, &temp[0], 17);
		write(STDERR_FILENO, ";", 1);
		write(STDERR_FILENO, &temp[17], 13);
	}
	else if ((*local)->error_checker == 6)
	{
		write(STDERR_FILENO, &temp[0], 17);
		write(STDERR_FILENO, ";", 1);
		write(STDERR_FILENO, ";", 1);
		write(STDERR_FILENO, &temp[17], 13);
	}
	else if ((*local)->error_checker == 7)
	{
		write(STDERR_FILENO, ": Can't open ", 13);
		write(STDERR_FILENO, &((*local)->av[1])[0], _strlen((*local)->av[1]));
		write(STDERR_FILENO, "\n", 1);
	}

	(*local)->exit_status = 2;
}

