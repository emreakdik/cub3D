#include "includes/cub3d.h"
#include <string.h> // strstr icin
#include <stdio.h> // bzero icin

int	parse_cub_file(t_all *s, char *file)
{
	int	fd;
	int	parse_result;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	s->map.cub_file = read_file_and_split_by_newline(fd);
	close(fd);
	if (!s->map.cub_file || !is_map_at_bottom(s->map.cub_file,
			ft_tablen(s->map.cub_file)))
		return (ft_strerror(-12));
	if (allocate_memory_for_map(s, s->map.cub_file) < 0)
		return (ft_strerror(-11));
	parse_result = extract_and_validate_map(s);
	ft_split_free(s->map.cub_file);
	if (parse_result == 0)
		return (final_configuration_check(s));
	else
		return (ft_strerror(parse_result));
}

void	draw_game_frame(t_all *s)
{
	ft_memset(&s->ray, 0, sizeof(t_ray));
	ft_memset(&s->hit, 0, sizeof(t_hit));
	render_frame(s);
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	free(s->img.ptr);
	free(s->img.adr);
}

int	initialize_and_run_game(t_all s)
{
	s.tex.c = NONE;
	s.tex.f = NONE;
	s.mlx.ptr = mlx_init();
	if (parse_cub_file(&s, s.map.file) == -1)
		return (close_application(&s, 0));
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3D");
	create_trig_value_table(&s);
	draw_game_frame(&s);
	mlx_hook(s.win.ptr, 2, 0, handle_key_press, &s);
	mlx_hook(s.win.ptr, 3, 0, handle_key_release, &s);
	mlx_hook(s.win.ptr, 17, 0, clean_up_and_exit, &s);
	mlx_loop_hook(s.mlx.ptr, update_player_position_and_view, &s);
	mlx_loop(s.mlx.ptr);
	return (1);
}

int	main(int ac, char **av)
{
	t_all	s;
	char	*extension;

	if (ac == 2)
	{
		/*burada seg var*/
		extension = strstr(av[1], ".cub"); // ft_strstr olacak
		if (strcmp(extension, ".cub") != 0) // ft_strcmp olacak
			return (ft_strerror(-20));
		ft_memset(&s, 0, sizeof(t_all));
		s.map.file = av[1];
		initialize_and_run_game(s);
	}
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
