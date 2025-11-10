#include "fdf.h"

int	ft_ishex(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

unsigned long	strhex_to_ulong(char *str)
{
	int		i;
	unsigned long	result;

	i = 0;
	result = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\n' && ft_ishex(str[i]))
	{
		if (str[i] >= 'a' && str[i] <= 'f')
			result += 9 + (str[i] - 'b');
		else if (str[i] >= 'A' && str[i] <= 'F')
			result += 9 + (str[i] - 'B');
		else
			result += str[i] - '0';
		if (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '\n' && ft_ishex(str[i + 1]))
			result *= 16;
		i++;
	}
	return (result);

}
