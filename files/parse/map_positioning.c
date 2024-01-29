#include "../includes/cub3d.h"

int	allocate_memory_for_map(t_all *s, char **cub_file)
{
	int	tab_len;

	tab_len = ft_tablen(cub_file);
	s->map.tab = malloc(sizeof(char *) * (tab_len + 1));
	if (s->map.tab == NULL)
		return (-11);
	return (0);
}

int	extract_and_validate_map(t_all *s)
{
   process_cub_file_lines(s);
	if (s->err.n < 0 || validate_and_fill_map(s))
		return (s->err.n);
	initialize_player_position(s);
	replace_spaces_with_walls(s);
	return (0);
}

int	locate_player_start_position(t_all *s, int *startX, int *startY)
{
	int	i;
	int	j;

	i = 0;
	while (s->map.tab[i])
	{
		j = 0;
		while (s->map.tab[i][j])
		{
			if (s->map.tab[i][j] == 'N' || s->map.tab[i][j] == 'S'
				|| s->map.tab[i][j] == 'E' || s->map.tab[i][j] == 'W')
			{
				*startX = i;
				*startY = j;
				break ;
			}
			j++;
		}
		if (*startX != -1)
			break ;
		i++;
	}
	if (*startX == -1)
		return (-1);
	return (0);
}

void	set_player_direction(t_all *s, char c)
{
	if (c == 'E' || c == 'W')
	{
		s->dir.x = 1;
		if (c == 'W')
			s->dir.x = -1;
	}
	else
		s->dir.x = 0;
	if (c == 'S' || c == 'N')
	{
		s->dir.y = 1;
		if (c == 'N')
			s->dir.y = -1;
	}
	else
		s->dir.y = 0;
	s->err.p++;
}
void	initialize_player_position(t_all *s)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (s->map.tab[++i])
	{
		j = -1;
		while (s->map.tab[i][++j])
		{
			c = s->map.tab[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				s->pos.y = (double)i + 0.5;
				s->pos.x = (double)j + 0.5;
				set_player_direction(s, c);
			}
		}
	}
}