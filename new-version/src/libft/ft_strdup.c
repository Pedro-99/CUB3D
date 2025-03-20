#include "cub3d.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		str_length;
	size_t	i;

	if (!s1)
		return (NULL);
	str_length = ft_strlen(s1);
	str = (char *)malloc(str_length + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup1(const char *s1, int len)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	str = (char *)malloc(len + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
