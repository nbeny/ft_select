#include "ft_select.h"

t_select	*ft_up_arrow(t_select *select, t_shell *shell)
{
	int			i;

	i = -1;
	if (select != NULL)
	{
		ft_clear_cursor(select, shell);
		while (++i != shell->nw_line && select->prev != NULL)
			select = select->prev;
		ft_print_cursor(select, shell);
	}
	return (select);
}

t_select	*ft_down_arrow(t_select *select, t_shell *shell)
{
	int			i;

	i = -1;
	if (select != NULL)
	{
		ft_clear_cursor(select, shell);
		while (++i != shell->nw_line && select->next != NULL)
			select = select->next;
		ft_print_cursor(select, shell);
	}
	return (select);
}

t_select	*ft_right_arrow(t_select *select, t_shell *shell)
{
	ft_clear_cursor(select, shell);
	if (select->next != NULL)
		select = select->next;
	else
	{
		while (select->prev != NULL)
			select = select->prev;
	}
	ft_print_cursor(select, shell);
	return (select);
}

t_select	*ft_left_arrow(t_select *select, t_shell *shell)
{
	ft_clear_cursor(select, shell);
	if (select->prev != NULL)
		select = select->prev;
	else
	{
		while (select->next != NULL)
			select = select->next;
	}
	ft_print_cursor(select, shell);
	return (select);
}


void	ft_keys_select(t_select *select, t_shell *shell)
{
	char	buff[3];

	while (42)
	{
		ft_bzero(buff, 3);
		read(0, buff, 3);
		if (buff[0] == 27)
		{
			if (buff[1] == 91 && buff[2] == 'A')
				select = ft_up_arrow(select, shell);
			if (buff[1] == 91 && buff[2] == 'B')
				select = ft_down_arrow(select, shell);
			if (buff[1] == 91 && buff[2] == 'C')
				select = ft_right_arrow(select, shell);
			if (buff[1] == 91 && buff[2] == 'D')
				select = ft_left_arrow(select, shell);
			if ((buff[1] == 0 || buff[1] == 27 || buff[1] == 10) &&
				(buff[2] == 0 || buff[2] == 27 || buff[2] == 10))
			{
				tcsetattr(0, NULL, &(shell->oldterm));
				exit(EXIT_SUCCESS);
			}
		}
	}
}
