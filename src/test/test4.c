#include "ft_select.h"

char			*xtgetstr(char *cap, char **area)
{
	char			*str;

	if ((str = tgetstr(cap, area)) == NULL)
    {
		ft_printf(2, "error: xtgetstr: Failed to get %e.\n", cap);
		exit(EXIT_FAILURE);
    }
	return (str);
}

int     main(int argc, char **argv)
{
	char  *term;
	char  bp[1024];
	char  t[4096];
	char  *area;
	char  *clstr;
	char  *sostr;
	char  *sestr;
	char  *cmstr;
	int   i;
 
	if ((term = getenv("TERM")) == NULL)
    {
		ft_putstr("can't determine terminal\n");
		exit(1);
    }
	if (tgetent(bp, term) != 1)
    {
		ft_putstr("problem with tgetent\n");
		exit(1);
    }
	area = t;
	clstr = xtgetstr("cl", &area);
	sostr = xtgetstr("so", &area);
	sestr = xtgetstr("se", &area);
	cmstr = xtgetstr("cm", &area);
	tputs(clstr, 0, ft_outc);
	i = 1;
	while (i < argc)
    {
		tputs(tgoto(cmstr, 0, i), 1, ft_outc);
		ft_putstr(argv[i]);
		i = i + 1;
    }
	ft_putstr("\n");
}
