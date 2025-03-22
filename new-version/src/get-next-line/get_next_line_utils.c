/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:13:06 by bzinedda          #+#    #+#             */
/*   Updated: 2024/05/16 12:27:46 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_free(char **ptr)
{
	if (!(*ptr))
		return (NULL);
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static void	init_lengths(int *len, char *rest, char *buffer, int *j)
{
	int	len1;
	int	len2;

	*j = 0;
	if (!rest)
		len1 = 0;
	else
		len1 = ft_strlen(rest);
	if (!buffer)
		len2 = 0;
	else
		len2 = ft_strlen(buffer);
	*len = len1 + len2;
}

char	*ft_strjoin(char *rest, char *buffer)
{
	char	*strjoin;
	int		i;
	int		j;
	int		len;

	i = 0;
	if (!rest && !(*buffer))
		return (NULL);
	init_lengths(&len, rest, buffer, &j);
	strjoin = malloc(len + 1);
	if (!strjoin)
		return (ft_free(&rest));
	if (rest && *rest)
	{
		while (rest[i])
		{
			strjoin[i] = rest[i];
			i++;
		}
	}
	while (buffer[j])
		strjoin[i++] = buffer[j++];
	strjoin[len] = '\0';
	free (rest);
	return (strjoin);
}
