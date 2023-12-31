/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 18:01:54 by cclaude           #+#    #+#             */
/*   Updated: 2023/12/31 23:56:48 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_spaceskip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
		|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

int	ft_atoi(char *line, int *i)
{
	int	num;

	num = 0;
	ft_spaceskip(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (num);
}

void	ft_strerror2(int err)
{
	if (err == -11)
		write(2, "Error : Malloc fail (map table)\n", 32);
	else if (err == -12)
		write(2, "Error : Invalid map\n", 20);
	else if (err == -13)
		write(2, "Error : Map isn't a rectangle\n", 30);
	else if (err == -14)
		write(2, "Error : No resolution specified\n", 32);
	else if (err == -15)
		write(2, "Error : Missing texture\n", 24);
	else if (err == -16)
		write(2, "Error : Missing floor/ceiling color\n", 26);
	else if (err == -17)
		write(2, "Error : No starting position\n", 29);
	else if (err == -18)
		write(2, "Error : Multiple starting positions\n", 36);
	else if (err == -19)
		write(2, "Error : Map isn't surrounded by walls\n", 38);
}

int	ft_strerror(int err)
{
	if (err == -1)
		write(2, "Error : Couldn't open file (FD)\n", 32);
	else if (err == -2)
		write(2, "Error : Couldn't parse file (GNL)\n", 34);
	else if (err == -3)
		write(2, "Error : Resolution specified twice\n", 35);
	else if (err == -4)
		write(2, "Error : Invalid resolution\n", 27);
	else if (err == -5)
		write(2, "Error : Floor/ceiling specified twice\n", 38);
	else if (err == -6)
		write(2, "Error : Invalid floor/ceiling line\n", 35);
	else if (err == -7)
		write(2, "Error : Texture path specified twice\n", 37);
	else if (err == -8)
		write(2, "Error : Malloc fail (texture path)\n", 35);
	else if (err == -9)
		write(2, "Error : Invalid texture image\n", 30);
	else if (err == -10)
		write(2, "Error : Invalid line in file\n", 29);
	else
		ft_strerror2(err);
	return (-1);
}
