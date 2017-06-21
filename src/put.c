#include "ft_select.h"

void	ft_print_select(t_select *select, t_shell *shell)
{
	t_select	*save;
	int			i;

	save = select;
	i = 0;
	while (save != NULL)
	{
		tputs(tgoto(shell->cursor, (save->pos_x - 1), save->pos_y), 1, ft_putchar);
		ft_printf(1, "[%-*s]", shell->word, save->name);		
		save = save->next;
	}
}

void	ft_clear_cursor(t_select *select, t_shell *shell)
{
	tputs(tgoto(shell->cursor, select->pos_x, select->pos_y), 1, ft_putchar);
	ft_printf(1, "\033[0m%-*s", shell->word, select->name);
}

void	ft_print_cursor(t_select *select, t_shell *shell)
{
	tputs(tgoto(shell->cursor, select->pos_x, select->pos_y), 1, ft_putchar);
	ft_printf(1, "\033[34;4m%-*s\033[0m", shell->word, select->name);
}
