/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers_func_stderr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:12:38 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/05 14:55:32 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_count_stderr(int n, int *count)
{
	long	nbr;

	nbr = (long)n;
	if (nbr < 0)
	{
		ft_putchar_count_stderr('-', count);
		nbr = nbr * (-1);
	}
	if (nbr >= 10)
		ft_putnbr_count_stderr(nbr / 10, count);
	ft_putchar_count_stderr((nbr % 10 + '0'), count);
}

void	ft_putaddress_count_stderr(uintptr_t address, int *count, int flag)
{
	if (flag == ON)
		ft_putstr_count_stderr("0x", count);
	if (address >= 16)
		ft_putaddress_count_stderr(address / 16, count, OFF);
	ft_putchar_count_stderr("0123456789abcdef"[address % 16], count);
}

void	ft_putunsigned_count_stderr(unsigned int u, int *count)
{
	if (u >= 10)
		ft_putunsigned_count_stderr(u / 10, count);
	ft_putchar_count_stderr((u % 10 + '0'), count);
}

void	ft_puthex_count_stderr(unsigned int u, int *count, char c)
{
	if (u >= 16)
		ft_puthex_count_stderr(u / 16, count, c);
	if (c == 'X')
		ft_putchar_count_stderr("0123456789ABCDEF"[u % 16], count);
	else
		ft_putchar_count_stderr("0123456789abcdef"[u % 16], count);
}
