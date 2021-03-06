/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <nbeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 10:09:56 by nbeny             #+#    #+#             */
/*   Updated: 2018/07/03 20:25:18 by nbeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "../ft_printf/include/ft_printf.h"
# include <termios.h>
# include <unistd.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>

typedef struct		s_scroll
{
	int				i;
	int				sc;
	int				y;
}					t_scroll;
typedef struct		s_shell
{
	struct termios	oldterm;
	struct termios	term;
	char			*xterm;
	char			*clear;
	char			*cursor;
	char			*shadow;
	char			*visible;
	int				word;
	int				ws_col;
	int				ws_row;
	int				nw_line;
	int				x;
	int				y;
	struct s_scroll	scroll;
	struct s_select	*select;
}					t_shell;
typedef struct		s_select
{
	char			*name;
	int				pos_x;
	int				pos_y;
	int				select;
	struct s_select	*next;
	struct s_select	*prev;
}					t_select;
typedef struct		s_pos
{
	int				i;
	int				x;
	int				y;
	int				res;
}					t_pos;

/*
**main
*/
void				ft_init_term(t_shell *shell);
int					ft_update_window(t_shell *shell);
int					main(int ac, char **av);
/*
**arg
*/
t_select			*ft_create_elem(t_select *begin_list, char *name);
t_select			*ft_list_push_back(t_select *begin_list, char *name);
t_scroll			ft_get_scroll(t_shell *shell, t_pos *p);
void				ft_previous_list(t_select *select, t_shell *shell);
t_select			*ft_mem_arguments(char **av, t_select *select,\
										t_shell *shell);
/*
**key
*/
t_select			*ft_up_arrow(t_select *select, t_shell *shell);
t_select			*ft_down_arrow(t_select *select, t_shell *shell);
t_select			*ft_right_arrow(t_select *select, t_shell *shell);
t_select			*ft_left_arrow(t_select *select, t_shell *shell);
void				ft_keys_select(t_select *select, t_shell *shell);
/*
**key2
*/
void				ft_sheck_pos(t_shell *term);
void				ft_up_arrow_norme(t_select *select, t_shell *shell);
void				ft_right_arrow_norme(t_select *select, t_shell *shell);
t_select			*ft_get_key(t_select *select, t_shell *shell);
/*
**put
*/
void				ft_print_select(t_select *select, t_shell *shell);
void				ft_clear_cursor(t_select *select, t_shell *shell);
void				ft_print_cursor(t_select *select, t_shell *shell);
void				ft_print_first_cursor(t_select *select, t_shell *shell);
void				ft_print_selection(t_select *select, t_shell *shell);
/*
**put2
*/
t_select			*ft_print_select_mid(t_shell *shell,\
											t_select *save, int i);
void				ft_print_select2(t_select *select, t_shell *shell,\
											t_select *save);
/*
**select
*/
void				init_p(t_pos *p);
void				ft_get_pos(t_select *select, t_shell *shell);
t_select			*ft_spacex(t_select *select, t_shell *shell);
void				ft_enter(t_select *select, t_shell *shell);
void				ft_found_printer(t_select *select, t_shell *shell);
/*
**signal
*/
void				*select_static(void);
void				sig_segv(int sig);
void				sig_stop(int sig);
void				sig_cont(int sig);
void				sig_int(int sig);
/*
**free
*/
void				ft_freedom(t_select *free);
#endif
