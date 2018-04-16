#include "ft_select.h"

volatile sig_atomic_t	lastpstp;

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
/*
void	sig_stop(int sig)
{
	t_shell			*shell;
//	struct winsize	ws;
	t_select		*select;

	shell = (t_shell *)select_static();
//	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	tcsetattr(0, TCSANOW, &(shell->oldterm));
	select = shell->select;
	while (select->prev != NULL)
		select = select->prev;
	shell->select = select;
	if (sig == SIGTSTP)
	{
//		SIG_DFL;
//		ioctl(1, TIOCSTI, &ws);
//		tputs(tgetstr("ke", NULL), 0, ft_putchar);
//		tputs(tgetstr("te", NULL), 0, ft_putchar);
//		tputs(tgetstr("ve", NULL), 0, ft_putchar);
//		tputs(tgetstr("cd", NULL), 0, ft_putchar);
//		fflush(stdout);
	}
}
*/

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
