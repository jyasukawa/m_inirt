/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:13:46 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/05 14:59:55 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	n_len;

	if (needle[0] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	n_len = ft_strlen(needle);
	i = 0;
	while (haystack[i] && (n_len + i) <= len)
	{
		if (ft_strncmp((&haystack[i]), needle, n_len) == 0)
			return ((char *)(&haystack[i]));
		i++;
	}
	return (NULL);
}
