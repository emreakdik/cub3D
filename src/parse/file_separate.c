#include "../../includes/cub3d.h"
#include <string.h>

int	load_xpm_image_to_texture(t_all *s, unsigned int **adr, char *file)
{
	int		fd;
	void	*img;
	int		tab[5];
	char 		*extension;
	
	extension = strstr(file, ".xpm");
	if (strcmp(extension, ".xpm") != 0)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	img = mlx_xpm_file_to_image(s->mlx.ptr, file, &tab[0], &tab[1]);
	if (img == NULL || tab[0] != 64 || tab[1] != 64)
		return (-1);
	*adr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	free(img);
	return (0);
}

int	parse_texture_path_and_load(t_all *s, unsigned int **adr, char *line, int *i)
{
	char	*file;
	int		j;

	if (*adr != NULL)
		return (-7);
	(*i) += 2;
	skip_whitespace_characters(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	file = malloc(sizeof(char) * (*i - j + 1));
	if (!file)
		return (-8);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = load_xpm_image_to_texture(s, adr, file);
	free(file);
	if (j == -1)
		return (-9);
	else
		return (0);
}

int	parse_and_set_resolution(t_all *s, char *line, int *i)
{
	if (s->win.x != 0 || s->win.y != 0)
		return (-3);
	(*i)++;
	s->win.x = ft_modified_atoi(line, i);
	s->win.y = ft_modified_atoi(line, i);
	if (s->win.x > 2560)
		s->win.x = 2560;
	if (s->win.y > 1400)
		s->win.y = 1400;
	skip_whitespace_characters(line, i);
	if (s->win.x <= 0 || s->win.y <= 0 || line[*i] != '\0')
		return (-4);
	return (0);
}

int	parse_and_set_color(unsigned int *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != NONE)
		return (-5);
	(*i)++;
	r = ft_modified_atoi(line, i);
	(*i)++;
	g = ft_modified_atoi(line, i);
	(*i)++;
	b = ft_modified_atoi(line, i);
	skip_whitespace_characters(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255) // rgb - olursa?
		return (-6);
	*color = r * 256 * 256 + g * 256 + b; // bakilir
	return (0);
}
