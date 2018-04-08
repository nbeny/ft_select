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
	res = shell->ws_col / (shell->word + 2);
	while (save != NULL)
	{
		if (i == res)
		{
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			i = 0;
		}
		ft_printf(1, "[%-*s]", shell->word, save->name);
		i++;
		save = save->next;
	}
	if (shell->scroll != 0)
	{
		i = shell->scroll;
		while (i != 0)
		{
			tputs(tgetstr("sr", NULL), 1, ft_putchar);
			i--;
		}
	}
//	tputs(tgetstr("rc", NULL), 1, ft_putchar);
//    tputs(tgetstr("kM", NULL), 1, ft_putchar);
}

void	ft_clear_cursor(t_select *select, t_shell *shell)
{
	tputs(tgoto(tgetstr("cm", NULL), select->pos_x, select->pos_y), 1, ft_putchar);
	ft_printf(1, "\033[0m%-*s", shell->word, select->name);
}

void	ft_print_cursor(t_select *select, t_shell *shell)
{
	tputs(tgoto(tgetstr("cm", NULL), select->pos_x, select->pos_y), 1, ft_putchar);
	ft_printf(1, "\033[34;4m%-*s\033[0m", shell->word, select->name);
}

void	ft_print_selection(t_select *select, t_shell *shell)
{
	tputs(tgoto(tgetstr("cm", NULL), select->pos_x, select->pos_y), 1, ft_putchar);
	ft_printf(1, "\033[34;7m%-*s\033[0m", shell->word, select->name);
}