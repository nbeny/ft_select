#include "ft_select.h"

int     voir_touche()
{
	char     buffer[3];
 
	while (1)
	{
		ft_bzero(buffer, 3);
		read(0, buffer, 3);
		if (buffer[0] == 27)
		{
			if (buffer[2] == '\0')
			{
				printf("C'est un escape !\n");
				return (0);
			}
			if (buffer[2] == 'A')
				printf("C'est une fleche du haut !\n");
			if (buffer[2] == 'B')
				printf("C'est une fleche du bas !\n");
			if (buffer[2] == 'C')
				printf("C'est une fleche du droite !\n");
			if (buffer[2] == 'D')
				printf("C'est une fleche du gauche !\n");
			if (buffer[2] == 'H')
				printf("C'est la touche home !\n");
			if (buffer[2] == 'F')
				printf("C'est la touche end !\n");
			if (buffer[2] == '5')
				printf("C'est la touche page up !\n");
			if (buffer[2] == '6')
				printf("C'est la touche page down !\n");
		}
	}
	return (0);
}

int              main(int ac, char **av, char **env)
{
	char           *name_term;
	struct termios term;
 
	(void)ac;
	(void)av;
	(void)env;
	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == -1)
		return (-1);
	// remplis la structure termios des possibilités du terminal.
	if (tcgetattr(0, &term) == -1)
		return (-1);
	voir_touche();
	printf("http://www.delorie.com/gnu/docs/bash/termcap.html");
	return (0);
}
