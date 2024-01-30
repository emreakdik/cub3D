#include "../../includes/cub3d.h"

int	clean_up_and_exit(t_all *s)
{
	int	i;

	i = 0;
	// split free verince seg vuruyor
	while (i < s->map.y)
		free(s->map.tab[i++]);
	// freelemek yerine destroy gerekebilr
	free(s->map.tab);
	free(s->tex.n);
	free(s->tex.s);
	free(s->tex.e);
	free(s->tex.w);
	free(s->stk);
	// mlx_destroy_image(s->mlx.ptr, s->img.ptr);
	mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	// buraya baska destroy image eklenmesi gerekebilir
	free(s->mlx.ptr);
	exit(0);
	return (1);
}

int	handle_key_press(int key, void *arg)
{
	t_all	*s;

	s = (t_all *)arg;
	if (key == ESC)
		close_application(s, 1);
	else if (key == W)
		s->key_w = 1;
	else if (key == A)
		s->key_a = 1;
	else if (key == S)
		s->key_s = 1;
	else if (key == D)
		s->key_d = 1;
	else if (key == LEFT)
		s->key_left = 1;
	else if (key == RIGHT)
		s->key_right = 1;
	return (1);
}

int	close_application(t_all *s, int win)
{
	ft_split_free(s->map.tab);
	free(s->tex.n);
	free(s->tex.s);
	free(s->tex.e);
	free(s->tex.w);
	// mlx_destroy_image(s->mlx.ptr, s->img.ptr);
	if (win == 1)
		mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	free(s->mlx.ptr);
	exit(0);
	return (1);
}

int	handle_key_release(int key, void *arg)
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
	return (1);
}

int	update_player_position_and_view(t_all *s)
{
	if (s->key_w)
		move_player_forward_back(s, 1);
	if (s->key_s)
		move_player_forward_back(s, -1);
	if (s->key_a)
		move_player_left_right(s, -1);
	if (s->key_d)
		move_player_left_right(s, 1);
	if (s->key_left)
		rotate_player_view(s, -1);
	if (s->key_right)
		rotate_player_view(s, 1);
	render_frame(s);
	return (1);
}
