#include "ft_select.h"

t_select	*ft_create_select(t_select *begin_list, char *name)
{
	t_select	*tmp;
	t_select	*select;

	tmp = begin_list;
	if (!(select = (t_select *)malloc(sizeof(t_select))))
	{
		ft_printf(2, "ft_select: malloc failed.\n");
		exit(EXIT_FAILURE);
	}
	select->name = ft_strdup(name);
	select->pos_x = 0;
	select->pos_y = 0;
	select->select = 0;
	select->next = NULL;
	select->prev = NULL;
	return (select);
}

t_select	*ft_list_push_back(t_select *begin_list, char *name)
{
	t_select	*tmp;
	t_select	*select;

	select = ft_create_select(begin_list, name);
	if (begin_list)
	{
		tmp = begin_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = select;
	}
	else
		return (select);
	return (begin_list);
}

void		ft_get_pos(t_select *select, t_shell *shell)
{
	t_pos		p;
	t_select	*save;

	save = select;
	p.i = 0;
	p.x = 0;
	p.y = 0;
	shell->nw_line = 1;
	p.res = shell->ws_col / (shell->word + 2);
	shell->nw_line = p.res;
	while (save != NULL)
	{
		p.x = (shell->word + 2) * p.i;
		save->pos_x = p.x + 1;
		save->pos_y = p.y;
		save = save->next;
		p.i++;
		if (p.i == p.res)
		{
			p.i = 0;
			p.x = 0;
			p.y++;
		}
	}
}

void		ft_previous_list(t_select *select, t_shell *shell)
{
	t_select	*save;
	t_select	*bef;
	t_shell		*s;

	s = shell;
	bef = select;
	save = select->next;
	while (save != NULL)
	{
		save->prev = bef;
		bef = bef->next;
		save = save->next;
	}
}

t_select	*ft_mem_arguments(char **av, t_select *select, t_shell *shell)
{
	int			i;

	i = 0;
	while (av[++i] != NULL)
		select = ft_list_push_back(select, av[i]);
	ft_previous_list(select, shell);
	i = 0;
	shell->word = (int)ft_strlen(av[1]);
	while (av[++i] != NULL)
	{
		if ((int)ft_strlen(av[i]) > shell->word)
			shell->word = (int)ft_strlen(av[i]);
	}
	ft_get_pos(select, shell);
/*
	while (select)
	{
		ft_printf(2, "[%i][%i]\n", select->pos_x, select->pos_y);
		ft_printf(2, "[%s]\n", select->name);
		select = select->next;
	}
	ft_printf(2, "{%i}\n", shell->word);
	exit(1);
*/
	return (select);
}
