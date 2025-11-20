/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_safe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:10:59 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/20 04:44:52 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	kill_error(char *message)
{
	perror(message);
	exit (0);
}

void	safe_kill(char **tab1, int **tab2, int **tab3)
{
	int	i;

	i = 0;
	if (tab1)
	{
		while (tab1[i] != NULL)
			free(tab1[i++]);
		free(tab1);
	}
	i = 0;
	if (tab2)
	{
		while (tab2[i] != NULL)
			free(tab2[i++]);
		free(tab2);
	}
	i = 0;
	if (tab3)
	{
		while (tab3[i] != NULL)
			free(tab3[i++]);
		free(tab3);
	}
	exit(0);
}

void	free_coordinates(int **coordinates)
{
	int	i;

	i = 0;
	while (coordinates[i] != NULL)
		free(coordinates[i++]);
	free(coordinates);
}

void	free_doublestr(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		free(strs[i++]);
	free(strs);
}
