#include "cub3d.h"

static	int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n'
		|| c == ' ' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long	result;
	int				sign;
	int				i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 9223372036854775807UL && (sign == 1))
			return (-1);
		if (result > 9223372036854775807UL && (sign == -1))
			return (0);
		i++;
	}
	return ((int)(result * sign));
}
