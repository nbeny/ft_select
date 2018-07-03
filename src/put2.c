/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 20:05:58 by nbeny             #+#    #+#             */
/*   Updated: 2018/07/03 20:24:53 by nbeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select	*ft_print_select_mid(t_shell *shell, t_select *save, int i)
{
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
	return (save);
}

void		ft_print_select2(t_select *select, t_shell *shell, t_select *save)
{
	int		i;

	i = 0;
	if (shell->scroll.i == shell->ws_row - 1)
		while (i != shell->nw_line - 1 && save != NULL)
		{
			if (save->select == 0)
				ft_printf(0, "[%-*s]", shell->word, save->name);
			if (save->select == 1)
				ft_printf(0, "\[\033[34;7m%-*s\033[0m]",\
							shell->word, save->name);
			save = save->next;
			i++;
		}
	save = select;
	while (save->next != NULL)
		save = save->next;
	if (shell->scroll.i != 0)
		while (shell->scroll.i != 0 && save != NULL)
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			tputs(tgetstr("cr", NULL), 1, ft_putchar);
			save = save->prev;
			shell->scroll.i--;
		}
}
