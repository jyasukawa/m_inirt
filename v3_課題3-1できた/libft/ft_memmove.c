/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:12:33 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/05 15:07:25 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	if (dst == NULL && src == NULL)
		return (NULL);
	if ((unsigned char *)dst < (const unsigned char *)src)
		return (ft_memcpy(dst, src, len));
	while (len > 0)
	{
		len--;
		((unsigned char *)dst)[len] = ((const unsigned char *)src)[len];
	}
	return (dst);
}
