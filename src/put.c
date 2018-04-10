#include "ft_select.h"

void	ft_print_select(t_select *select, t_shell *shell)
{
	t_select	*save;
	int			i;
	int			res;

//    tputs(tgetstr("im", NULL), 1, ft_putchar);
//    tputs(tgetstr("sc", NULL), 1, ft_putchar);
	save = select;
	i = 0;
	if (shell->scroll.i != 0)
		while (shell->scroll.i != 0)
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			shell->scroll.i--;
		}
	res = shell->ws_col / (shell->word + 2);
	while (save != NULL)
	{
		if (i == res)
		{
			i = 0;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			tputs(tgetstr("cr", NULL), 1, ft_putchar);
			shell->scroll.i++;
		}
		ft_printf(1, "[%-*s]", shell->word, save->name);
		i++;
		save = save->next;
	}
	if (shell->scroll.i != 0)
		while (shell->scroll.i != 0)
		{
			if (shell->scroll.i <= shell->scroll.sc)
			{
//				ft_printf(2, "I m here !\n");
				tputs(tgetstr("sf", NULL), 1, ft_putchar);
			}
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			shell->scroll.i--;
		}
//	tputs(tgetstr("ho", NULL), 1, ft_putchar);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
//	tputs(tgetstr("rc", NULL), 1, ft_putchar);
//	tputs(tgetstr("kM", NULL), 1, ft_putchar);
}

void	ft_clear_cursor(t_select *select, t_shell *shell)
{
	int		i;

	i = 0;
	while (i != select->pos_x)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		i++;
	}
	ft_printf(1, "\033[0m%-*s", shell->word, select->name);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
}

void	ft_print_cursor(t_select *select, t_shell *shell)
{
	int		i;

	i = 0;
	while (i != select->pos_x)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		i++;
	}
	ft_printf(1, "\033[34;4m%-*s\033[0m", shell->word, select->name);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
}

void	ft_print_selection(t_select *select, t_shell *shell)
{
	int		i;

	i = 0;
	while (i != select->pos_x)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		i++;
	}
	ft_printf(1, "\033[34;7m%-*s\033[0m", shell->word, select->name);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
}
