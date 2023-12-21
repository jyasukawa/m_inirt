/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:12:41 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/05 15:03:28 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_count(int n, int *count)
{
	long	nbr;

	nbr = (long)n;
	if (nbr < 0)
	{
		ft_putchar_count('-', count);
		nbr = nbr * (-1);
	}
	if (nbr >= 10)
		ft_putnbr_count(nbr / 10, count);
	ft_putchar_count((nbr % 10 + '0'), count);
}

void	ft_putaddress_count(uintptr_t address, int *count, int flag)
{
	if (flag == ON)
		ft_putstr_count("0x", count);
	if (address >= 16)
		ft_putaddress_count(address / 16, count, OFF);
	ft_putchar_count("0123456789abcdef"[address % 16], count);
}

void	ft_putunsigned_count(unsigned int u, int *count)
{
	if (u >= 10)
		ft_putunsigned_count(u / 10, count);
	ft_putchar_count((u % 10 + '0'), count);
}

void	ft_puthex_count(unsigned int u, int *count, char c)
{
	if (u >= 16)
		ft_puthex_count(u / 16, count, c);
	if (c == 'X')
		ft_putchar_count("0123456789ABCDEF"[u % 16], count);
	else
		ft_putchar_count("0123456789abcdef"[u % 16], count);
}
