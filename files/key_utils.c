/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 23:46:30 by emre              #+#    #+#             */
/*   Updated: 2024/01/01 00:08:20 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key_release(int key, void *arg)
{
	t_all	*s;

	s = (t_all *)arg;
	if (key == W)
		s->key_w = 0;
	else if (key == A)
		s->key_a = 0;
	else if (key == S)
		s->key_s = 0;
	else if (key == D)
		s->key_d = 0;
	else if (key == LEFT)
		s->key_left = 0;
	else if (key == RIGHT)
		s->key_right = 0;
	ft_draw(arg);
	return (1);
}

int	ft_update(t_all *s)
{
	if (s->key_w)
		ft_move(s, 1);
	if (s->key_a)
		ft_strafe(s, -1);
	if (s->key_s)
		ft_move(s, -1);
	if (s->key_d)
		ft_strafe(s, 1);
	if (s->key_left)
		ft_rotate(s, -1);
	if (s->key_right)
		ft_rotate(s, 1);
	ft_draw(s);
	return (1);
}
