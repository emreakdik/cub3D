/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre <emre@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:09 by cclaude           #+#    #+#             */
/*   Updated: 2024/01/04 12:33:54 by emre             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlxopengl/mlx.h"
# include <fcntl.h>
# include <math.h>
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

# define SPEED 3
# define TURN 0.025
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
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
	char			**tab;
	int				x;
	int				y;
	int				spr;
}					t_map;

typedef struct s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	*i;
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

typedef struct s_spr
{
	double			x;
	double			y;
	double			d;
}					t_spr;

typedef struct s_stk
{
	double			x;
	double			y;
	double			d;
}					t_stk;

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
	t_spr			*spr;
	t_stk			*stk;
	int				key_w;
	int				key_a;
	int				key_s;
	int				key_d;
	int				key_left;
	int				key_right;
}					t_all;

int					ft_update(t_all *s);
int					ft_key_release(int key, void *arg);
void				ft_init(char *cub);
void				ft_declare(t_all s, char *cub);
int					ft_cubed(t_all s, char *cub);
void				ft_draw(t_all *s);

int					ft_parse(t_all *s, char *cub);
int					get_next_line(int fd, char **line);
int					ft_line(t_all *s, char *line);

int					ft_map(t_all *s, char *line, int *i);
char				*ft_slab(t_all *s, char *line, int *i);
int					ft_slablen(t_all *s, char *line);
int					ft_texture(t_all *s, unsigned int **adr, char *line,
						int *i);
int					ft_xpm(t_all *s, unsigned int **adr, char *file);

int					ft_slist(t_all *s);
void				ft_pos(t_all *s);
int					ft_colors(unsigned int *color, char *line, int *i);
int					ft_res(t_all *s, char *line, int *i);

int					ft_parcheck(t_all *s);
int					ft_mapcheck(t_all *s);
int					ft_savecheck(char *arg, char *save);
int					ft_namecheck(char *arg, char *ext);

int					ft_key(int key, void *arg);
void				ft_rotate(t_all *s, double c);
void				ft_strafe(t_all *s, double c);
void				ft_move(t_all *s, double c);
int					ft_close(t_all *s, int win);

void				ft_screen(t_all *s);
void				ft_ray(t_all *s);
void				ft_dir(t_all *s);
void				ft_ver(t_all *s);
void				ft_hor(t_all *s);

void				ft_stock(t_all *s);
int					ft_size(t_all *s);
void				ft_column(t_all *s, int start);
unsigned int		ft_pixel(t_all *s, double i);

void				ft_sprite(t_all *s);
void				ft_sorder(t_all *s);
void				ft_slocate(t_all *s, double dirx, double diry, double dist);
void				ft_sdraw(t_all *s, int loc, double dist);
unsigned int		ft_spixel(t_all *s, int index, unsigned int col);

char				*error(char *stock);
int					newline_check(char *stock, int read_size);
char				*buf_join(char *stock, char *buf);
char				*stock_trim(char *stock);
char				*get_line(char *stock);

int					ft_atoi(char *line, int *i);
int					ft_spaceskip(char *line, int *i);
int					ft_strerror(int err);

#endif
