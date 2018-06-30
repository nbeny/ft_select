/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 17:42:12 by nbeny             #+#    #+#             */
/*   Updated: 2018/06/30 18:18:35 by nbeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	}
	if (shell->scroll.i == select->pos_y)
		ft_print_cursor(select, shell);
	else if (shell->scroll.i > select->pos_y)
	{
		shell->scroll.i--;
		ft_sheck_pos(shell);
		if (shell->y == 1)
			tputs(tgetstr("sr", NULL), 1, ft_putchar);
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgetstr("cr", NULL), 1, ft_putchar);
		if (shell->y == 1)
			ft_found_printer(select, shell);
		ft_print_cursor(select, shell);
	}
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
	}
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
	if (select->select == 0)
		ft_clear_cursor(select, shell);
	if (select->select == 1)
		ft_print_selection(select, shell);
	if (select->prev != NULL)
		select = select->prev;
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
	return (select);
}

void		ft_keys_select(t_select *select, t_shell *shell)
{
	char	buff[3];

	while (42)
	{
		shell->select = select;
		signal(SIGINT, sig_int);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGCONT, sig_cont);
		select = shell->select;
		if (ft_update_window(shell))
		{
			tputs(tgetstr("cl", NULL), 1, ft_putchar);
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
