/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:09 by cclaude           #+#    #+#             */
/*   Updated: 2024/01/30 14:19:03 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlxopengl/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define NONE 0xFF000000
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define MAGENTA 0x00FF00FF
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define SPEED 5
# define TURN 0.03
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# ifndef MAX_INT
#  define MAX_INT 2147483647
# endif
# endif

typedef struct s_mlx
{
	void			*ptr;
}					t_mlx;

typedef struct s_win
{
	void			*ptr;
	int				x;
	int				y;
}					t_win;

typedef struct s_img
{
	void			*ptr;
	unsigned int	*adr;
	int				fsh;
}					t_img;

typedef struct s_err
{
	int				n;
	int				m;
	int				p;
}					t_err;

typedef struct s_map
{
	int				x;
	int				y;
	char			**cub_file;
	char			**tab;
	char			*file; // path yapilabilir
}					t_map;

typedef struct s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	c;
	unsigned int	f;
}					t_tex;

typedef struct s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct s_dir
{
	double			x;
	double			y;
	double			a;
}					t_dir;

typedef struct s_ray
{
	double			x;
	double			y;
	int				i;
	double			v;
	double			w;
}					t_ray;

typedef struct s_hit
{
	double			x;
	double			y;
	double			d;
}					t_hit;

typedef struct s_stk
{
	double			x;
	double			y;
	double			d;
}					t_stk;

typedef struct s_trg 
{
	double sin[7200];
	double cos[7200];
	double hypot[];
} t_trg;

typedef struct s_all
{
	t_mlx			mlx;
	t_win			win;
	t_img			img;
	t_err			err;
	t_map			map;
	t_tex			tex;
	t_pos			pos;
	t_dir			dir;
	t_ray			ray;
	t_hit			hit;
	t_stk			*stk;
	t_trg			*trg;
	int				key_w;
	int				key_a;
	int				key_s;
	int				key_d;
	int				key_left;
	int				key_right;
}					t_all;

/* Parse */
void				parse_config_line(t_all *s, char *line, int j);
void				process_cub_file_lines(t_all *s);
char				*read_file_to_string(int fd);
char				**read_file_and_split_by_newline(int fd);
void				replace_spaces_with_walls(t_all *s);
int					load_xpm_image_to_texture(t_all *s, unsigned int **adr,
						char *file);
int					parse_texture_path_and_load(t_all *s, unsigned int **adr,
						char *line, int *i);
int					parse_and_set_resolution(t_all *s, char *line, int *i);
int					parse_and_set_color(unsigned int *color, char *line,
						int *i);
bool				is_map_at_bottom(char **lines, int line_count);
int					recursive_map_validation(t_all *s, int y, int x,
						char **visited);
int					initialize_visited(t_all *s, char ***visited);
int					validate_and_fill_map(t_all *s);
int					final_configuration_check(t_all *s);
int					allocate_memory_for_map(t_all *s, char **cub_file);
int					extract_and_validate_map(t_all *s);
int					locate_player_start_position(t_all *s, int *startX,
						int *startY);
void				set_player_direction(t_all *s, char c);
void				initialize_player_position(t_all *s);

/* Screen */
unsigned int		get_texture_pixel_color(t_all *s, double i);
void				draw_vertical_slice(t_all *s, int size);
int					calculate_slice_height(t_all *s);
void				store_ray_hit_info(t_all *s);
void				calculate_ray_vector(t_all *s);
void				determine_ray_direction(t_all *s);
void				perform_vertical_ray_cast(t_all *s);
void				perform_horizontal_ray_cast(t_all *s);
void				render_frame(t_all *s);
void	create_trig_value_table(t_all *s);

/* Hook */
int					clean_up_and_exit(t_all *s);
int					handle_key_press(int key, void *arg);
int					close_application(t_all *s, int win);
int					handle_key_release(int key, void *arg);
int					update_player_position_and_view(t_all *s);
void				move_player_forward_back(t_all *s, double c);
void				move_player_left_right(t_all *s, double c);
void				rotate_player_view(t_all *s, double c);

/* Cub3d.c */
int					parse_cub_file(t_all *s, char *file);
void				draw_game_frame(t_all *s);
int					initialize_and_run_game(t_all s);

/* Tools */
int					ft_tablen(char **tab);
int					new_line_counter(char *line);
int					skip_whitespace_characters(char *line, int *i);
void				ft_strerror2(int err);
int					ft_strerror(int err);
#endif
