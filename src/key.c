#include "ft_select.h"

t_select	*ft_up_arrow(t_select *select, t_shell *shell)
{
	int			i;

	i = -1;
	if (select != NULL)
	{
		if (select->select == 0)
			ft_clear_cursor(select, shell);
		if (select->select == 1)
			ft_print_selection(select, shell);
		while (++i != shell->nw_line && select->prev != NULL)
			select = select->prev;
//		ft_print_cursor(select, shell);
	}
	if (shell->scroll.i == select->pos_y)
		ft_print_cursor(select, shell);
	else if (shell->scroll.i > select->pos_y)
	{
		shell->scroll.i--;
		if (shell->scroll.i > shell->ws_row)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
		ft_print_cursor(select, shell);
	}
/*
	if (shell->scroll < select->pos_y)
		ft_print_cursor(select, shell);
	else
	{
		shell->scroll--;
		tputs(tgetstr("sr", NULL), 1, ft_putchar);
		ft_print_cursor(select, shell);
	}
*/
	return (select);
}

t_select	*ft_down_arrow(t_select *select, t_shell *shell)
{
	int			i;

	i = -1;
	if (select != NULL)
	{
		if (select->select == 0)
			ft_clear_cursor(select, shell);
		if (select->select == 1)
			ft_print_selection(select, shell);
		while (++i != shell->nw_line && select->next != NULL)
			select = select->next;
		if (shell->scroll.i == select->pos_y)
			ft_print_cursor(select, shell);
		else if (shell->scroll.i < select->pos_y)
		{
			shell->scroll.i++;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			tputs(tgetstr("cr", NULL), 1, ft_putchar);
			ft_print_cursor(select, shell);
		}
	}
	return (select);
}

t_select	*ft_right_arrow(t_select *select, t_shell *shell)
{
	if (select->select == 0)
		ft_clear_cursor(select, shell);
	if (select->select == 1)
		ft_print_selection(select, shell);
	if (select->next != NULL)
		select = select->next;
	else
	{
		while (select->prev != NULL)
			select = select->prev;
	}
//	ft_printf(2,"[%d][%d]\n", shell->scroll.i, select->pos_y);
	if (shell->scroll.i == select->pos_y)
		ft_print_cursor(select, shell);
	else if (shell->scroll.i < select->pos_y)
	{
			shell->scroll.i++;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			tputs(tgetstr("cr", NULL), 1, ft_putchar);
			ft_print_cursor(select, shell);
	}
	else
	{
		while (shell->scroll.i != 0)
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			shell->scroll.i--;
		}
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
		ft_print_cursor(select, shell);
	}
	return (select);
}

t_select	*ft_left_arrow(t_select *select, t_shell *shell)
{
	t_select	*s;

	if (select->select == 0)
		ft_clear_cursor(select, shell);
	if (select->select == 1)
		ft_print_selection(select, shell);
	if (select->prev != NULL)
		select = select->prev;
	else
	{
		s = select;
		while (select->next != NULL)
			select = select->next;
	}
	if (shell->scroll.i == select->pos_y)
		ft_print_cursor(select, shell);
	else if (shell->scroll.i > select->pos_y &&\
			s->pos_y != 0 && s->pos_x != 1)
	{
		shell->scroll.i--;
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
		ft_print_cursor(select, shell);
	}
	else
	{
		while (shell->scroll.i != shell->scroll.y - 1)
		{
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			shell->scroll.i++;
		}
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
		ft_print_cursor(select, shell);
	}
/*
	else
	{
		while (shell->scroll.i != shell->scroll.y)
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			shell->scroll.i++;
		}
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
	}
*/
	return (select);
}


void	ft_keys_select(t_select *select, t_shell *shell)
{
	char	buff[3];

	while (42)
	{
		if (ft_update_window(shell))
		{
			tputs(tgetstr("cl", NULL), 1, ft_putchar);
//			tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar);
			ft_get_pos(select, shell);
			ft_print_select(select, shell);
			while (select->prev != NULL)
				select = select->prev;
			ft_print_cursor(select, shell);
		}
		ft_bzero(buff, 3);
		read(0, buff, 3);
		if (buff[0] == 27)
		{
			if (buff[1] == 91 && buff[2] == 'A')
				select = ft_up_arrow(select, shell);
			if (buff[1] == 91 && buff[2] == 'B')
				select = ft_down_arrow(select, shell);
			if (buff[1] == 91 && buff[2] == 'C')
				select = ft_right_arrow(select, shell);
			if (buff[1] == 91 && buff[2] == 'D')
				select = ft_left_arrow(select, shell);
			if ((buff[1] == 0 || buff[1] == 27 || buff[1] == 10) &&
				(buff[2] == 0 || buff[2] == 27 || buff[2] == 10))
			{
				tputs(tgetstr("ve", NULL), 1, ft_putchar);
				tcsetattr(0, TCSADRAIN, &(shell->oldterm));
				exit(EXIT_SUCCESS);
			}
		}
		if (buff[0] == ' ' && buff[1] == 0)
			select = ft_spacex(select, shell);
		if (buff[0] == '\n' && buff[1] == 0)
			ft_enter(select, shell);
	}
}
