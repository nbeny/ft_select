#include "ft_select.h"

t_select	*ft_spacex(t_select *select, t_shell *shell)
{
	if (select->select == 0)
	{
		ft_print_selection(select, shell);
		select->select = 1;
		select = ft_right_arrow(select, shell);
	}
	else
	{
		ft_print_cursor(select, shell);
		select->select = 0;
	}
	return (select);
}

void		ft_enter(t_select *select, t_shell *shell)
{
	t_select	*s;

	s = select;
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	while (s->next != NULL)
		s = s->next;
	tputs(tgoto(tgetstr("cm", NULL), (select->pos_x + shell->word + 1), select->pos_y), 1, ft_putchar);
	tcsetattr(0, TCSADRAIN, &(shell->oldterm));
	while(s->prev != NULL)
		s = s->prev;
	ft_printf(1, "\n");
	while(s != NULL)
	{
		if (s->select == 1)
			ft_printf(1, "%s ", s->name);
		s = s->next;
	}
	exit(EXIT_SUCCESS);
}
