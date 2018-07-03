/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 17:42:24 by nbeny             #+#    #+#             */
/*   Updated: 2018/07/03 20:26:13 by nbeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_print_select(t_select *select, t_shell *shell)
{
	t_select	*save;
	int			i;

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
	save = ft_print_select_mid(shell, save, i);
	ft_print_select2(select, shell, save);
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
