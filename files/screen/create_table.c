#include "../includes/cub3d.h"
#define TABLE_SIZE 7200                                        

void	create_trig_value_table(t_all *s)
{
	s->trg = malloc(sizeof(t_trg));
	int i = 0;
	while (i < TABLE_SIZE)
	{
		double radian = (i * (360.0 / TABLE_SIZE)) * M_PI / 180.0;
		s->trg->sin[i] = sin(radian);
		s->trg->cos[i] = cos(radian);
		i++;
	}
}
