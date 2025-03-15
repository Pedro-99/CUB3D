#include "cub3d.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			converted_c;

	if (!s)
		return (NULL);
	converted_c = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == converted_c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == converted_c)
		return ((char *) &s[i]);
	return (NULL);
}
