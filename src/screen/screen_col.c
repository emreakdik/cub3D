#include "../../includes/cub3d.h"

unsigned int	get_texture_pixel_color(t_all *s, double i)
{
	int	index;

	if ((int)s->hit.y == s->hit.y) // tum floor fonksiyonlarini int'e cevirdim cunku o da tabanliyor amk
	{
		index = 64 * (int)(64 * i) + 64 * (s->hit.x - (int)s->hit.x);
		if (s->ray.w == 1)
			return (s->tex.s[index]);
		else if (s->ray.w == 0)
			return (s->tex.n[index]);
	}
	else if ((int)s->hit.x == s->hit.x)
	{
		index = 64 * (int)(64 * i) + 64 * (s->hit.y - (int)s->hit.y);
		if (s->ray.v == 1)
			return (s->tex.e[index]);
		else if (s->ray.v == 0)
			return (s->tex.w[index]);
	}
	return (BLACK);
}

void	draw_vertical_slice(t_all *s, int size_of_wall)
{
	unsigned int	color;
	int				start_of_wall;
	int				pixel_index;

	start_of_wall = s->win.x * (s->win.y - size_of_wall) / 2;
	if (size_of_wall > s->win.y)
		pixel_index = (size_of_wall - s->win.y) / 2;
	else
		pixel_index = 0;
	color = s->tex.c;
	while (s->ray.i < s->win.x * s->win.y)
	{
		if (s->ray.i >= start_of_wall && pixel_index < size_of_wall)
		{
			color = get_texture_pixel_color(s, (double)pixel_index / size_of_wall);
			pixel_index++;
		}
		else if (pixel_index == size_of_wall)
			color = s->tex.f;
		s->img.adr[s->ray.i] = mlx_get_color_value(s->mlx.ptr, color); // mlx_get_color_value fonksiyonunu sildim
		s->ray.i += s->win.x;
	}
	s->ray.i -= s->win.x * s->win.y;
}

int	calculate_slice_height(t_all *s)
{
	double	correc;
	double	fisheye;

	fisheye = fabs((double)s->ray.i / (s->win.x / 2) - 1);
	fisheye *= 33 * M_PI / 180;
	correc = (double)s->hit.d * cos(fisheye);
	return (round(s->win.y / correc));
}

void	store_ray_hit_info(t_all *s)
{
	s->stk[s->ray.i].x = s->ray.x;
	s->stk[s->ray.i].y = s->ray.y;
	s->stk[s->ray.i].d = s->hit.d;
}

