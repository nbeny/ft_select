/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:23:32 by nbeny             #+#    #+#             */
/*   Updated: 2018/04/08 15:39:52 by nbeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int		ft_putchar(int c)
{
	wchar_t wc;

	wc = (wchar_t)c;
	write(1, &wc, 1);
	return(0);
}
