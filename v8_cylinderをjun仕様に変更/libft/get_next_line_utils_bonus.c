/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:14:10 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/05 15:06:17 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_null(char *s, char c)
{
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_free(char *buffer, char *tmp, int *is_error)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (buffer == NULL)
	{
		buffer = ft_calloc_forone(1, 1);
		if (buffer == NULL)
			return (ft_error_found(buffer, is_error));
	}
	str = malloc(sizeof(char) * (ft_strlen(buffer) + ft_strlen(tmp) + 1));
	if (str == NULL)
		return (ft_error_found(buffer, is_error));
	i = 0;
	while (buffer[i])
	{
		str[i] = buffer[i];
		i++;
	}
	j = 0;
	while (tmp[j])
		str[i++] = tmp[j++];
	str[i] = '\0';
	free(buffer);
	return (str);
}

char	*ft_calloc_forone(size_t count, size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size * count));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_error_found(char *buffer, int *is_error)
{
	free(buffer);
	buffer = NULL;
	*is_error = YES;
	return (NULL);
}
