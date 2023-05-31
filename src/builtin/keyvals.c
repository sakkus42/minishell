#include "builtin.h"

void	set_tmp(char **tmp, int *i)
{
	char	**str;

	if (*tmp)
		free(*tmp);
	str = ft_split(g_data.env[*i], '=');
	*tmp = ft_strdup(str[1]);
	free(str[0]);
	free(str[1]);
}

void	set_keys(char *keyval, int *find, int *i)
{
	char *key1;
	char *key2;

	while (g_data.env[++(*i)])
	{
		key1 = ft_substr(keyval, 0, ft_strchr(keyval, '=') - keyval);
		//eski dizininde "OLDPWD="'nin '=' yerine kadar kesip,
		// key1'e atıyor.
		key2 = ft_substr(g_data.env[*i], 0, ft_strchr(g_data.env[*i], '=')
								//şu anki dizini, key2'ye atıyor.
								- g_data.env[*i]);
		if (!ft_strcmp(key1, key2)) //iki key aynıysa, yani ikiside OLDPWD ise,
									// o zaman find 1 arttırılır.
			(*find)++;
		free(key1);
		free(key2);
	}
}