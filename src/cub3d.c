#include "../includes/cub3d.h"

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


int	initialize_and_run_game(t_all s)
{
	int	bpp;
	int	sl;
	int	end;

	s.tex.c = NONE;
	s.tex.f = NONE;
	s.mlx.ptr = mlx_init();
	if (parse_cub_file(&s, s.map.file) == -1)
		return (close_application(&s, 0));
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3D");
	create_trig_value_table(&s);
	s.img.ptr = mlx_new_image(s.mlx.ptr, s.win.x, s.win.y);
	s.img.adr = (unsigned int *)mlx_get_data_addr(s.img.ptr, &bpp, &sl, &end);
	s.stk = malloc(sizeof(t_stk) * s.win.x);
	mlx_hook(s.win.ptr, 2, 0, handle_key_press, &s);
	mlx_hook(s.win.ptr, 3, 0, handle_key_release, &s);
	mlx_hook(s.win.ptr, 17, 0, clean_up_and_exit, &s);
	mlx_do_sync(s.mlx.ptr);
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
		/*burada seg var .cub olmayinca seg veriyor*/
		extension = strstr(av[1], ".cub");  // ft_strstr olacak
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
