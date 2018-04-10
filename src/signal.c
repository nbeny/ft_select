#include "ft_select.h"

void	*select_static(void)
{
	static t_shell	shell;

	return (&shell);
}

void	sig_exe(int sig)
{
	t_shell	*shell;

	if (sig == SIGSTOP)
	{
		shell = (t_shell *)select_static();
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
		tcsetattr(0, TCSADRAIN, &(shell->oldterm));
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
//          tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar);
		while (select->prev != NULL)
			select = select->prev;
		ft_get_pos(select, shell);
		ft_print_select(select, shell);
		while (select->prev != NULL)
			select = select->prev;
		ft_print_cursor(select, shell);
	}
}

void	sig_init(int sig)
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
