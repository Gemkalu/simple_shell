#include "shell.h"

/**
* checkbuild - This checks if the command is a buildin
* @arv: These array of arguments
* Return:   t   his points to function that takes arv and returns void
*/
void(*checkbuild(char **arv))(char **arv)
{
	int i, j;
	mybuild T[] = {
		{"exit", gexitt},
		{"env", genv},
		{"setenv", g_setenv},
		{"unsetenv", g_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; T[i].name; i++)
	{
		j = 0;
		if (T[i].name[j] == arv[0][j])
		{
			for (j = 0; arv[0][j]; j++)
			{
				if (T[i].name[j] != arv[0][j])
					break;
			}
			if (!arv[0][j])
				return (T[i].func);
		}
	}
	return (0);
}
