#include "cub3d.h"

static	int	ft_is_char_found(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (s1)
	{
		if (ft_is_char_found(*s1, set))
			s1++;
		else
			break ;
	}
	len = ft_strlen(s1);
	while (len > 0)
	{
		if (ft_is_char_found(s1[len - 1], set))
			len--;
		else
			break ;
	}
	strtrim = (char *)malloc(len + 1);
	if (!strtrim)
		return (NULL);
	ft_strlcpy(strtrim, s1, len + 1);
	return (strtrim);
}
