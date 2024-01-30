#include "libft.h"
#include <stdlib.h>

int	ft_split_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (1);
}

char	**ft_modified_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	str = (char **)malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		k = 0;
		str[j] = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (!str[j])
			return (NULL);
		while (s[i] && s[i] == c)
			str[j][k++] = s[i++];
		while (s[i] && s[i] != c)
			str[j][k++] = s[i++];
		str[j][k] = '\0';
		j++;
	}
	str[j] = NULL;
	return (str);
}