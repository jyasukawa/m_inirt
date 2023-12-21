/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:13:53 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/05 15:00:20 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strchr(set, (int)s1[i]))
		i++;
	len = ft_strlen(s1);
	if (i == len)
		return (ft_strdup(""));
	while (len != i && ft_strchr(set, (int)s1[len]))
		len--;
	return (ft_substr(&s1[i], 0, (len - i + 1)));
}
