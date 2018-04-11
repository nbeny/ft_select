#include "ft_select.h"

void	ft_init_term(t_shell *shell)
{
	if ((shell->xterm = getenv("TERM")) == NULL)
	{
		ft_printf(2, "Terminale not initialized.\n");
		exit(EXIT_FAILURE);
	}
	if (tgetent(0, shell->xterm) != 1)
	{
		ft_printf(2, "Tgetent failure.\n");
		exit(EXIT_FAILURE);
	}
	tcgetattr(0, &(shell->oldterm));
	tcgetattr(0, &(shell->term));
	shell->term.c_lflag &= ~ICANON;
	shell->term.c_lflag &= ~ECHO;
	shell->term.c_cc[VMIN] = 1;
	shell->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &(shell->term));
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	tputs(tgetstr("vi", NULL), 1, ft_putchar);
}

int		ft_update_window(t_shell *shell)
{
	struct winsize	ws;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
	{
		ft_printf(2, "ioctl failed.\n");
		exit(EXIT_FAILURE);
	}
	if (shell->ws_col != ws.ws_col)
	{
		shell->ws_col = ws.ws_col;
		shell->ws_row = ws.ws_row;
		return (1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_shell		*shell;
	t_select	*select;

	select = NULL;
	if (ac > 1)
	{
//		signal(SIGCONT, sig_cont);
		shell = select_static();
		ft_init_term(shell);
		ft_update_window(shell);
		select = ft_mem_arguments(av, select, shell);	
		ft_print_select(select, shell);
		ft_print_cursor(select, shell);
		ft_keys_select(select, shell);
	}
	return (0);
}
