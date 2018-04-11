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

void	sig_stop(int sig)
{
	t_shell	*shell;

	if (sig == SIGSTOP)
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
		tcsetattr(0, TCSADRAIN, &(shell->term));
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
