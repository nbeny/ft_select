#include "ft_select.h"

void	ft_print_select(t_select *select, t_shell *shell)
{
	t_select	*save;
	int			i;
//	int			res;

//    tputs(tgetstr("im", NULL), 1, ft_putchar);
//    tputs(tgetstr("sc", NULL), 1, ft_putchar);
//	while (select->prev != NULL)
//		select = select->prev;
	save = select;
	i = 0;
	if (shell->scroll.i != 0)
	{
		while (shell->scroll.i != 0)
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			shell->scroll.i--;
		}
	}
	while (save != NULL && shell->scroll.i != shell->ws_row - 1)
	{
		if (i == shell->nw_line)
		{
			i = 0;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			tputs(tgetstr("cr", NULL), 1, ft_putchar);
			++shell->scroll.i;
		}
		if (save->select == 0)
			ft_printf(0, "[%-*s]", shell->word, save->name);
		if (save->select == 1)
			ft_printf(0, "\[\033[34;7m%-*s\033[0m]", shell->word, save->name);
		i++;
		save = save->next;
	}
	i = 0;
	if (shell->scroll.i == shell->ws_row - 1)
		while (i != shell->nw_line - 1 && save != NULL)
		{
			if (save->select == 0)
				ft_printf(0, "[%-*s]", shell->word, save->name);
			if (save->select == 1)
				ft_printf(0, "\[\033[34;7m%-*s\033[0m]", shell->word, save->name);
			save = save->next;
			i++;
		}
	save = select;
	while (save->next != NULL)
		save = save->next;
	if (shell->scroll.i != 0)
		while (shell->scroll.i != 0 && save != NULL)
		{
/*			if (shell->scroll.i <= shell->scroll.sc)
			{
				ft_printf(1, "[%-*s]", shell->word, save->name);
				tputs(tgetstr("sr", NULL), 1, ft_putchar);
				}*/
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			tputs(tgetstr("cr", NULL), 1, ft_putchar);
			save = save->prev;
			shell->scroll.i--;
		}
//	tputs(tgetstr("ho", NULL), 1, ft_putchar);
//	tputs(tgetstr("rc", NULL), 1, ft_putchar);
//	tputs(tgetstr("kM", NULL), 1, ft_putchar);
}

void	ft_clear_cursor(t_select *select, t_shell *shell)
{
	int		i;

	i = 0;
	while (i != select->pos_x - 1)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		i++;
	}
	ft_printf(0, "\[\033[0m%-*s]", shell->word, select->name);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
}

void	ft_print_cursor(t_select *select, t_shell *shell)
{
	int		i;

	i = 0;
	while (i != select->pos_x - 1)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		i++;
	}
	ft_printf(0, "\[\033[34;4m%-*s\033[0m]", shell->word, select->name);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
}

void	ft_print_first_cursor(t_select *select, t_shell *shell)
{
	int		i;

	i = 0;
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	ft_printf(0, "\[\033[34;4m%-*s\033[0m]", shell->word, select->name);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
}

void	ft_print_selection(t_select *select, t_shell *shell)
{
	int		i;

	i = 0;
	while (i != select->pos_x - 1)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		i++;
	}
	ft_printf(0, "\[\033[34;7m%-*s\033[0m]", shell->word, select->name);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
}
