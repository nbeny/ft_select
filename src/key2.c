/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:14:40 by nbeny             #+#    #+#             */
/*   Updated: 2018/06/30 21:33:57 by nbeny            ###   ########.fr       */
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

void		ft_up_arrow_norme(t_select *select, t_shell *shell)
{
	if (select->select == 0)
		ft_clear_cursor(select, shell);
	if (select->select == 1)
		ft_print_selection(select, shell);
}

void		ft_right_arrow_norme(t_select *select, t_shell *shell)
{
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
}

t_select	*ft_get_arrow(t_select *select, t_shell *shell, char *buff)
{
	if (buff[1] == 91 && buff[2] == 'A')
		select = ft_up_arrow(select, shell);
	if (buff[1] == 91 && buff[2] == 'B')
		select = ft_down_arrow(select, shell);
	if (buff[1] == 91 && buff[2] == 'C')
		select = ft_right_arrow(select, shell);
	if (buff[1] == 91 && buff[2] == 'D')
		select = ft_left_arrow(select, shell);
	return (select);
}

t_select	*ft_get_key(t_select *select, t_shell *shell)
{
	char	buff[3];

	ft_bzero(buff, 3);
	read(0, buff, 3);
	if (buff[0] == 27)
	{
		select = ft_get_arrow(select, shell, buff);
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
	return (select);
}
