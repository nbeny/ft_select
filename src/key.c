#include "ft_select.h"

void    ft_sheck_pos(t_shell *term)
{
    struct winsize  ws;
    char            *ansi;
    char            *buff;
    char            *tmp;

    if ((ansi = ft_strnew(10)) == NULL)
        return ;
    if ((buff = ft_strnew(50)) == NULL)
        return ;
    if (ioctl(0, TIOCGWINSZ, &ws) == -1)
        return ;
    term->ws_row = ws.ws_row;
    term->ws_col = ws.ws_col;
    ft_printf(0, "\E[6n");
    while (ft_strchr(buff, 'R') == NULL)
    {
        ft_bzero(buff, 10);
        read(0, buff, 10);
        tmp = ansi;
        ansi = ft_strjoin(tmp, buff);
        ft_strdel(&tmp);
    }
    term->y = ft_atoi(&ansi[2]);
    term->x = ft_atoi(&ft_strchr(&ansi[2], ';')[1]);
    ft_strdel(&buff);
    ft_strdel(&ansi);
}

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
		ft_sheck_pos(shell);
//		ft_printf(2, "shell->y = %d", shell->y);
		if (shell->y == 1)
			tputs(tgetstr("sr", NULL), 1, ft_putchar);
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
		if (shell->y == 1)
			ft_found_printer(select, shell);
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
			ft_found_printer(select, shell);
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
		ft_print_cursor(select, shell);
		return (select);
//		while (select->prev != NULL)
//			select = select->prev;
	}
//	ft_printf(2,"[%d][%d]\n", shell->scroll.i, select->pos_y);
	if (shell->scroll.i == select->pos_y)
		ft_print_cursor(select, shell);
	else if (shell->scroll.i < select->pos_y)
	{
			shell->scroll.i++;
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			tputs(tgetstr("cr", NULL), 1, ft_putchar);
			ft_found_printer(select, shell);
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
		ft_found_printer(select, shell);
		ft_print_cursor(select, shell);
	}
	return (select);
}

t_select	*ft_left_arrow(t_select *select, t_shell *shell)
{
//	t_select	*s;

	if (select->select == 0)
		ft_clear_cursor(select, shell);
	if (select->select == 1)
		ft_print_selection(select, shell);
	if (select->prev != NULL)
		select = select->prev;
/*	else
	{
		ft_print_cursor(select, shell);
		return (select);
//		s = select;
//		while (select->next != NULL)
//			select = select->next;
}*/
	if (shell->scroll.i == select->pos_y)
		ft_print_cursor(select, shell);
	else if (shell->scroll.i > select->pos_y)
	{
		shell->scroll.i--;
		ft_sheck_pos(shell);
		if (shell->y == 1 && select->pos_x > 4)
			tputs(tgetstr("sr", NULL), 1, ft_putchar);
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
		if (shell->y == 1 && select->pos_x > 4)
			ft_found_printer(select, shell);
		ft_print_cursor(select, shell);
	}
	/*
	else
	{
		ft_sheck_pos(shell);
		while (shell->scroll.i != shell->scroll.y - 1)
		{
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			shell->scroll.i++;
		}
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
		ft_print_cursor(select, shell);
	}
	*/
	/*
	if (shell->scroll.i == select->pos_y)
		ft_print_cursor(select, shell);
	else if (shell->scroll.i > select->pos_y)
	{
		shell->scroll.i--;
		ft_sheck_pos(shell);
//		ft_printf(2, "shell->y = %d", shell->y);
		if (shell->y == 1)
			tputs(tgetstr("sr", NULL), 1, ft_putchar);
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
		ft_print_cursor(select, shell);
	}
	*/
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
		shell->select = select;
		signal(SIGINT, sig_int);
//		signal(SIGTSTP, sig_stop);
		signal(SIGCONT, sig_cont);
//		signal(SIGKILL, sig_segv);
		select = shell->select;
		if (ft_update_window(shell))
		{
			tputs(tgetstr("cl", NULL), 1, ft_putchar);
//			tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar);
			while (select->prev != NULL)
				select = select->prev;
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
