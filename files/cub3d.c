/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:04 by cclaude           #+#    #+#             */
/*   Updated: 2024/01/04 22:49:02 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> // bzero icin

void	ft_draw(t_all *s)
{
	bzero(&s->ray, sizeof(t_ray)); // ft_bzero olacak
	bzero(&s->hit, sizeof(t_hit)); // ft_bzero olacak
	ft_screen(s);
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	free(s->img.ptr);
	free(s->img.adr);
}

int	ft_cubed(t_all s, char *cub)
{
	s.mlx.ptr = mlx_init();
	if (ft_parse(&s, cub) == -1)
		return (ft_close(&s, 0));
	ft_rotate(&s, 1);
	ft_move(&s, 1);
	ft_rotate(&s, -1);
	ft_move(&s, -1);
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3D");
	ft_draw(&s);
	mlx_hook(s.win.ptr, 2, 0, ft_key, &s);
	mlx_hook(s.win.ptr, 3, 0, ft_key_release, &s);
	mlx_loop_hook(s.mlx.ptr, ft_update, &s);
	mlx_loop(s.mlx.ptr);
	return (1);
}

int	main(int ac, char **av)
{
	t_all	s;

	if (ac == 2 && ft_namecheck(av[1], "cub"))
	{
		bzero(&s, sizeof(t_all)); // ft_bzero olacak
		s.tex.c = NONE;
		s.tex.f = NONE;
		ft_cubed(s, av[1]);
	}
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
