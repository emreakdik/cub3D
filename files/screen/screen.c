#include "../includes/cub3d.h"

void	calculate_ray_vector(t_all *s)
{
	double	angle;
	double	dist;

	angle = ((double)s->ray.i - (s->win.x / 2)) * 33 / (s->win.x / 2);
	angle = angle * M_PI / 180;
	s->ray.x = s->dir.x * cos(angle) - s->dir.y * sin(angle);
	s->ray.y = s->dir.y * cos(angle) + s->dir.x * sin(angle);
	dist = hypot(s->ray.x, s->ray.y);
	s->ray.x /= dist;
	s->ray.y /= dist;
}

void	determine_ray_direction(t_all *s)
{
	if (s->ray.x >= 0)
		s->ray.v = 1;
	else
		s->ray.v = 0;
	if (s->ray.y >= 0)
		s->ray.w = 1;
	else
		s->ray.w = 0;
}

void	perform_vertical_ray_cast(t_all *s)
{
	double	x;
	double	y;

	x = floor(s->pos.x) + s->ray.v;
	y = s->pos.y + ((x - s->pos.x) * (s->ray.y / s->ray.x));
	while ((int)floor(y) > 0 && (int)floor(y) < s->map.y)
	{
		if (s->map.tab[(int)floor(y)][(int)(x - 1 + s->ray.v)] == '1')
		{
			s->hit.x = x;
			s->hit.y = y;
			s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
			return ;
		}
		x += (2 * s->ray.v - 1);
		y += (2 * s->ray.v - 1) * s->ray.y / s->ray.x;
	}
	s->hit.x = s->pos.x;
	s->hit.y = s->pos.y;
	s->hit.d = MAX_INT;
}

void	perform_horizontal_ray_cast(t_all *s)
{
	double	y;
	double	x;
	int		map_width;
	double	distance;

	y = floor(s->pos.y) + s->ray.w;
	x = s->pos.x + (y - s->pos.y) * (s->ray.x / s->ray.y);
	map_width = 0;
	while (1)
	{
		map_width = ft_strlen(s->map.tab[(int)floor(y)]);
		if ((int)floor(x) <= 0 || (int)floor(x) >= map_width)
			break ;
		if (s->map.tab[(int)(y - 1 + s->ray.w)][(int)floor(x)] == '1')
		{
			distance = hypot(x - s->pos.x, y - s->pos.y);
			if (s->hit.d > distance)
			{
				s->hit.x = x;
				s->hit.y = y;
				s->hit.d = distance;
			}
			return ;
		}
		y += (2 * s->ray.w - 1);
		x += (2 * s->ray.w - 1) * s->ray.x / s->ray.y;
		if (floor(y) <= 0 || floor(y) >= s->map.y)
			break ;
	}
}

void	render_frame(t_all *s)
{
	int	bpp;
	int	sl;
	int	end;

	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.adr = (unsigned int *)mlx_get_data_addr(s->img.ptr, &bpp, &sl, &end);
	s->stk = malloc(sizeof(t_stk) * s->win.x);
	while (s->ray.i < s->win.x)
	{
		calculate_ray_vector(s);
		determine_ray_direction(s);
		perform_vertical_ray_cast(s);
		perform_horizontal_ray_cast(s);
		store_ray_hit_info(s);
		draw_vertical_slice(s, calculate_slice_height(s));
		s->ray.i++;
	}
}