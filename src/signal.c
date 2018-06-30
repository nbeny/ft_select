/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 17:42:38 by nbeny             #+#    #+#             */
/*   Updated: 2018/06/30 17:59:18 by nbeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	*select_static(void)
{
	static t_shell	shell;

	return (&shell);
}

void	sig_segv(int sig)
{
	t_shell	*shell;

	if (sig == SIGSEGV)
	{
		shell = (t_shell *)select_static();
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
		tcsetattr(0, TCSADRAIN, &(shell->oldterm));
		exit(EXIT_SUCCESS);
	}
}

void	sig_cont(int sig)
{
	t_shell		*shell;
	t_select	*select;

	shell = NULL;
	if (sig == SIGCONT)
	{
		shell = (t_shell *)select_static();
		select = shell->select;
		ft_init_term(shell);
		while (select->prev != NULL)
			select = select->prev;
		ft_get_pos(select, shell);
		ft_print_select(select, shell);
		while (select->prev != NULL)
			select = select->prev;
		shell->select = select;
		ft_print_cursor(select, shell);
	}
}

void	sig_int(int sig)
{
	t_shell	*shell;

	if (sig == SIGINT)
	{
		shell = (t_shell *)select_static();
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
		tcsetattr(0, TCSADRAIN, &(shell->oldterm));
		exit(EXIT_SUCCESS);
	}
}
