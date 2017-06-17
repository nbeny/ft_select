#include "ft_select.h"

int     main(int argc, char **argv)
{
	struct termios t;
	int   i;
	int   j;
	char  *xterm;
	char  *cmstr;
	char  *clstr;
	char  *kustr;
	char  *kdstr;
	char  *klstr;
	char  *krstr;
	char  buf[4096];
 
	if ((xterm = getenv("TERM")) == NULL)
    {
		ft_putstr("Impossible de déterminer le terminal\n");
		exit(1);
    }
	if (tgetent(0, xterm) != 1)
    {
		ft_putstr("Erreur avec getent\n");
		exit(1);
    }
	cmstr = tgetstr("cm", NULL);
	clstr = tgetstr("cl", NULL);
	kustr = tgetstr("ku", NULL);
	klstr = tgetstr("kl", NULL);
	krstr = tgetstr("kr", NULL);
	tputs(clstr, 1, ft_putchar);
	i = 0;
	while (i  <  argc)
    {
		ft_putstr(argv[i]);
		ft_putchar('\n');
		i++;
    }
	tputs(tgoto(cmstr, 0, 0), 1, ft_putchar);
	tcgetattr(0, &t);
	t.c_lflag &= ~ICANON;
	t.c_lflag &= ~ECHO;
	t.c_cc[VMIN] = 1;
	t.c_cc[VTIME] = 0;
	int x = 0;
	int y = 0;
	tcsetattr(0, NULL, &t);
	while (42)
	{
		ft_bzero(buf, 5);
		read(0, buf, 5);
		if (buf[2] == 'A')
			tputs(tgoto(cmstr, x, --y), 1, ft_putchar);
		if (buf[2] == 'B')
			tputs(tgoto(cmstr, x, ++y), 1, ft_putchar);
		if (buf[2] == 'C')
			tputs(tgoto(cmstr, ++x, y), 1, ft_putchar);
		if (buf[2] == 'D')
			tputs(tgoto(cmstr, --x, y), 1, ft_putchar);
		j = 0;
	}
}
