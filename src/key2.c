/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:14:40 by nbeny             #+#    #+#             */
/*   Updated: 2018/06/30 18:16:10 by nbeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		ft_sheck_pos(t_shell *term)
{
	struct winsize	ws;
	char			*ansi;
	char			*buff;
	char			*tmp;

	if ((ansi = ft_strnew(10)) == NULL || ioctl(0, TIOCGWINSZ, &ws) == -1)
		return ;
	if ((buff = ft_strnew(50)) == NULL)
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
