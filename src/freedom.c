/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 17:42:05 by nbeny             #+#    #+#             */
/*   Updated: 2018/06/30 17:42:08 by nbeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_freedom(t_select *select)
{
	t_select	*f;
	t_select	*s;

	s = select;
	f = NULL;
	while (s->prev != NULL)
		s = s->prev;
	while (s != NULL)
	{
		f = s;
		ft_strdel(&(f->name));
		s = s->next;
		free(f);
		f = NULL;
	}
}
