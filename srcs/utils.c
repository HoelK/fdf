/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:42:29 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/11 19:37:58 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_isnum(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_ishex(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F'));
}

int	str_to_color(char *str)
{
	int				i;
	int				result;

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
		if (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '\n'
			&& ft_ishex(str[i + 1]))
			result *= 16;
		i++;
	}
	return (result);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		minus;
	int		result;

	i = 0;
	minus = 0;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			minus = 1;
		i++;
	}
	while (ft_isnum(nptr[i]))
	{
		result += nptr[i] - '0';
		if (ft_isnum(nptr[i + 1]))
			result *= 10;
		i++;
	}
	if (minus)
		return (-result);
	return (result);
}
