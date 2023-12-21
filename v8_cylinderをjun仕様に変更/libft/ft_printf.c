/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:12:45 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/05 14:56:06 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_check_format(char c, va_list *ap, int *count, size_t *i)
{
	if (c == 'c')
		ft_putchar_count(va_arg(*ap, int), count);
	else if (c == 's')
		ft_putstr_count(va_arg(*ap, char *), count);
	else if (c == 'p')
		ft_putaddress_count(va_arg(*ap, uintptr_t), count, ON);
	else if (c == 'd' || c == 'i')
		ft_putnbr_count(va_arg(*ap, int), count);
	else if (c == 'u')
		ft_putunsigned_count(va_arg(*ap, unsigned int), count);
	else if (c == 'x' || c == 'X')
		ft_puthex_count(va_arg(*ap, unsigned int), count, c);
	else if (c == '%')
		ft_putchar_count('%', count);
	else
		(*i)--;
}

int	ft_printf(char *format, ...)
{
	va_list	ap;
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			ft_check_format(format[i], &ap, &count, &i);
			i++;
		}
		else
		{
			ft_putchar_count(format[i], &count);
			i++;
		}
	}
	va_end(ap);
	return (count);
}
