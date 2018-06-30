/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 17:40:06 by nbeny             #+#    #+#             */
/*   Updated: 2018/06/30 17:51:09 by nbeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		init_p(t_pos *p)
{
	p->i = 0;
	p->x = 0;
	p->y = 0;
}

void		ft_found_printer(t_select *select, t_shell *shell)
{
	t_select	*min;
	t_select	*max;
	t_select	*s;

	s = select;
	while (s->prev != NULL && s->prev->pos_x < s->pos_x)
		s = s->prev;
	min = s;
	while (s->next != NULL && s->next->pos_x > s->pos_x)
		s = s->next;
	max = s;
	while (min != NULL && min != max)
	{
		if (min->select == 0)
			ft_printf(0, "[%-*s]", shell->word, min->name);
		if (min->select == 1)
			ft_printf(0, "\[\033[34;7m%-*s\033[0m]", shell->word, min->name);
		min = min->next;
	}
	if (min->select == 0)
		ft_printf(0, "[%-*s]", shell->word, min->name);
	if (min->select == 1)
		ft_printf(0, "\[\033[34;7m%-*s\033[0m]", shell->word, min->name);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
}

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
	tcsetattr(0, TCSADRAIN, &(shell->oldterm));
	while (s->prev != NULL)
	{
		if (s->prev != NULL && s->pos_y != s->prev->pos_y)
			ft_printf(1, "\n");
		s = s->prev;
	}
	while (s != NULL)
	{
		if (s->select == 1)
			ft_printf(1, "%s ", s->name);
		s = s->next;
	}
	exit(EXIT_SUCCESS);
}
