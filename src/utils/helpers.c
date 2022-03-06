#include "minishell.h"

void	ft_free_string_arrays(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

char	**ft_split_single(char const *s, char c)
{
	char	**strs;
	int		i;

	if (!s || !c)
		return (NULL);

	i = 0;
	while(s[i] != c)
		i++;
	if (i == 0)
		return (NULL);

	strs = malloc(sizeof(char *) * 3);
	if (!strs)
		return (NULL);

	strs[0] = malloc(sizeof(char) * (i + 1));
	if(!strs[0])
		return (strs);
	ft_strlcpy(strs[0], s, i + 1);

	strs[1] = malloc(sizeof(char) * (ft_strlen(ft_strchr(s, c))));
	if(!strs[1])
		return (strs);
	ft_strlcpy(strs[1], &ft_strchr(s, c)[1], ft_strlen(ft_strchr(s, c)));
	
	strs[2] = NULL;
	return (strs);
}