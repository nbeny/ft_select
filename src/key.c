/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 17:42:12 by nbeny             #+#    #+#             */
/*   Updated: 2018/06/30 21:30:07 by nbeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select	*ft_up_arrow(t_select *select, t_shell *shell)
{
	int			i;

	i = -1;
	if (select != NULL)
	{
		ft_up_arrow_norme(select, shell);
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
	ft_right_arrow_norme(select, shell);
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
		select = ft_get_key(select, shell);
	}
}
