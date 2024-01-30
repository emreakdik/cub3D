#include "../../includes/cub3d.h"

void	move_player_forward_back(t_all *s, double c)
{
	s->pos.x += c * (s->dir.x * SPEED / 100);
	if (s->map.tab[(int)s->pos.y][(int)s->pos.x] == '1')
		s->pos.x -= c * (s->dir.x * SPEED / 100);
	s->pos.y += c * (s->dir.y * SPEED / 100);
	if (s->map.tab[(int)s->pos.y][(int)s->pos.x] == '1')
		s->pos.y -= c * (s->dir.y * SPEED / 100);
}

void	move_player_left_right(t_all *s, double c)
{
	s->pos.x -= c * (s->dir.y * SPEED / 100);
	if (s->map.tab[(int)s->pos.y][(int)s->pos.x] == '1')
		s->pos.x += c * (s->dir.y * SPEED / 100);
	s->pos.y += c * (s->dir.x * SPEED / 100);
	if (s->map.tab[(int)s->pos.y][(int)s->pos.x] == '1')
		s->pos.y -= c * (s->dir.x * SPEED / 100);
}

void	rotate_player_view(t_all *s, double c)
{
	double	dist;

	s->dir.x = s->dir.x * cos(c * TURN) - s->dir.y * sin(c * TURN);
	s->dir.y = s->dir.y * cos(c * TURN) + s->dir.x * sin(c * TURN);
	dist = hypot(s->dir.x, s->dir.y);
	s->dir.x /= dist;
	s->dir.y /= dist;
}
