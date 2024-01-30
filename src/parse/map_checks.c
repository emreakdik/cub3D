#include "../../includes/cub3d.h"

bool	is_map_at_bottom(char **lines, int line_count)
{
	int		i;
	bool	non_map_line_found_after_map;

	i = line_count - 1;
	non_map_line_found_after_map = false;
	while (i >= 0)
	{
		if (ft_strspn(lines[i], " 10NSWE\n") == (size_t)ft_strlen(lines[i]))
		{
			if (non_map_line_found_after_map)
				return (false);
		}
		else
			non_map_line_found_after_map = true;
		i--;
	}
	return (true);
}

int	recursive_map_validation(t_all *s, int y, int x, char **visited)
{
	if (!s->map.tab[y] || !s->map.tab[y][0])
		return (-1);
	if (y < 0 || y >= s->map.y || visited[y][x] || s->map.tab[y][x] == '1')
		return (1);
	if (s->map.tab[y][x] == '0' && (!s->map.tab[y - 1] || !s->map.tab[y + 1]
			|| !s->map.tab[y - 1][x] || !s->map.tab[y + 1][x]))
		return (-1);
	if (s->map.tab[y][x] != '0' && s->map.tab[y][x] != 'N'
		&& s->map.tab[y][x] != 'S' && s->map.tab[y][x] != 'E'
		&& s->map.tab[y][x] != 'W') // haritanin icinde 0,N,S,E,W disinda birsey varsa hata veriliyor
		return (-1);
	visited[y][x] = '1';
	if (recursive_map_validation(s, y - 1, x, visited) == -1) // Yukari
		return (-1);
	if (recursive_map_validation(s, y + 1, x, visited) == -1) // Asagi
		return (-1);
	if (recursive_map_validation(s, y, x - 1, visited) == -1) // Sol
		return (-1);
	if (recursive_map_validation(s, y, x + 1, visited) == -1) // Sag
		return (-1);
	return (1);
}

int	initialize_visited(t_all *s, char ***visited)
{
	int	i;

	*visited = malloc(sizeof(char *) * s->map.y);
	if (!*visited)
		return (-1);
	// 0'la dolu sanal harita olusturulup visited degiskeninde tutuluyor
	i = 0;
	while (i < s->map.y)
	{
		(*visited)[i] = malloc(sizeof(char) * (ft_strlen(s->map.tab[i]) + 1));
		if (!(*visited)[i]) // mallocta sikinti varsa oncekiler kapatiliyor
		{
			while (i > 0)
				free((*visited)[--i]);
			free(*visited);
			return (-1);
		}
		memset((*visited)[i], 0, ft_strlen(s->map.tab[i]) + 1); // 0'la dolduruluyor libft olacak
		i++;
	}
	return (0);
}
int	validate_and_fill_map(t_all *s)
{
	char	**visited;
	int		startX;
	int		startY;

	startX = -1;
	startY = -1;
	if (initialize_visited(s, &visited) < 0){ // visited degiskeni olusturuluyor
		s->err.n = -11;
		return (-1);
	}
	if (locate_player_start_position(s, &startX, &startY) < 0){
		s->err.n = -17;
		return (-1);
	}
	if (recursive_map_validation(s, startX, startY, visited) <= 0){
		s->err.n = -12;
		return (-1);
	}
	replace_spaces_with_walls(s);

	return (0);
}

int	final_configuration_check(t_all *s)
{
	if (s->win.x <= 0 || s->win.y <= 0)
		return (ft_strerror(-14));
	else if ((s->tex.n == NULL || s->tex.s == NULL || s->tex.e == NULL)
		|| (s->tex.w == NULL))
		return (ft_strerror(-15));
	else if (s->tex.c == NONE || s->tex.f == NONE)
		return (ft_strerror(-16));
	else if (s->err.p == 0)
		return (ft_strerror(-17));
	else if (s->err.p > 1)
		return (ft_strerror(-18));
	return (1);
}