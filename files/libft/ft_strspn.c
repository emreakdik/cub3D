#include "../includes/cub3d.h"
#include <stdlib.h>

size_t	ft_strspn(const char *str, const char *accept)
{
	size_t	size;
	size_t	ret;

	ret = 0;
	size = 0;
	while (str[size] != '\0')
	{
		if (!(ft_strchr(accept, str[size])))
			return (ret);
		else
			ret++;
		size++;
	}
	return (0);
}