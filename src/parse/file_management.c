#include "../../includes/cub3d.h"

void	parse_config_line(t_all *s, char *line, int j)
{
	skip_whitespace_characters(line, &j);
	if (line[j] == '1' || s->err.m == 1)
	{
		s->map.tab[s->map.y++] = strdup(line);
		s->err.m = 1;
	}
	else if (line[j] == 'R' && line[j + 1] == ' ')
		s->err.n = parse_and_set_resolution(s, line, &j);
	else if (line[j] == 'N' && line[j + 1] == 'O' && line[j + 2] == ' ')
		s->err.n = parse_texture_path_and_load(s, &s->tex.n, line, &j);
	else if (line[j] == 'S' && line[j + 1] == 'O' && line[j + 2] == ' ')
		s->err.n = parse_texture_path_and_load(s, &s->tex.s, line, &j);
	else if (line[j] == 'W' && line[j + 1] == 'E' && line[j + 2] == ' ')
		s->err.n = parse_texture_path_and_load(s, &s->tex.w, line, &j);
	else if (line[j] == 'E' && line[j + 1] == 'A' && line[j + 2] == ' ')
		s->err.n = parse_texture_path_and_load(s, &s->tex.e, line, &j);
	else if (line[j] == 'F' && line[j + 1] == ' ')
		s->err.n = parse_and_set_color(&s->tex.f, line, &j);
	else if (line[j] == 'C' && line[j + 1] == ' ')
		s->err.n = parse_and_set_color(&s->tex.c, line, &j);
}

void	process_cub_file_lines(t_all *s)
{
	int		i;
	char	*line;

	i = 0;
	while (s->map.cub_file[i])
	{
		line = s->map.cub_file[i];
		if (new_line_counter(line) > 1 && s->err.m == 1)
			s->err.n = -1;
		parse_config_line(s, line, 0);
		i++;
	}
}

char	*read_file_to_string(int fd)
{
	char	*str;
	char	*buf;
	int		ret;

	str = (char *)malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		buf[ret] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	**read_file_and_split_by_newline(int fd)
{
	char	*file_content;
	char	**split_content;

	file_content = read_file_to_string(fd);
	split_content = ft_modified_split(file_content, '\n'); // ismini ft_modified_split yap
	free(file_content);
	return (split_content);
}

void	replace_spaces_with_walls(t_all *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s->map.tab[i])
	{
		j = 0;
		while (s->map.tab[i][j])
		{
			if (s->map.tab[i][j] == ' ')
				s->map.tab[i][j] = '1';
			j++;
		}
		i++;
	}
}