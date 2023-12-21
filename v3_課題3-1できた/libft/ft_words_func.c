/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:14:05 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/05 14:14:07 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_count(int c, int *count)
{
	if (*count == INT_MAX || *count == -1)
	{
		*count = -1;
		return ;
	}
	write(1, &c, 1);
	(*count)++;
}

void	ft_putstr_count(char *s, int *count)
{
	size_t	i;

	i = 0;
	if (s == NULL)
	{
		ft_putstr_count("(null)", count);
		return ;
	}
	while (s[i])
	{
		ft_putchar_count(s[i], count);
		i++;
	}
}
