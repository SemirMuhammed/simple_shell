#include "main.h"

/**
 * _strlen - gets string length
 * @str: NULL terminated string
 *
 * Return: length of string
 */
size_t _strlen(char *str)
{
	size_t sc;

	if (str == NULL)
		return (0);

	for (sc = 0; str[sc]; sc++)
		continue;

	return (sc);
}

/**
 * get_mem - Allocates enough memory using malloc or realloc
 * @ptr: Pointer to the variable that need dynamic memory
 * @size: number of bytes to allocate
 *
 * Return: 0 on Success or 1 on Failure
 */
int get_mem(char **ptr, size_t size)
{
	if (*ptr != NULL)
	{
		*ptr = (char *) realloc(*ptr, sizeof(char) * size);
		if (*ptr == NULL)
		{
			return (1);
		}
	}
	else
	{
		*ptr = (char *) malloc(sizeof(char) * size);
		if (*ptr == NULL)
		{
			return (1);
		}
	}

	return (0);
}

/**
 * itoa - int to string conversion
 * @number: int value
 *
 * Return: string literal of number
 */
char *itoa(int number)
{
	size_t sc = 0, size = 2;
	char *str = NULL;

	if (get_mem(&str, size) == 1)
		return (NULL);
	if (number == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	while (number)
	{
		str[0] = '0' + (number % 10);
		number /= 10;
		if (number)
		{
			size++;
			if (get_mem(&str, size) == 1)
				return (NULL);
			for (sc = size - 1; sc > 0; sc--)
				str[sc] = str[sc - 1];
		}
	}
	str[size - 1] = '\0';

	return (str);
}

