#include "builtin.h"

void	ft_cd(char *dest, char *old_dir)
{
	char	*key;

	getcwd(g_data.path, 4096);
	if (!dest)//dizin yoksa hata verir
	{
		key = get_env("HOME");
		if (!key)
			printf("minishell : HOME not set\n");
		if (chdir(key) == -1)
			printf("çalişmadi\n");
		free(key);
	}
	else//Varsa
	{	
		if (access(dest, X_OK) == 0)//yazılan varsa, dizin değiştirilir.
			chdir(dest);
		else if (ENOENT == errno)//ENOENT, No such file or directory sinyali ve bunun hatası doğrulanırsa, içeriye girer.
			printf("minishell: cd: %s: No such file or directory\n", dest);
	}
	update_env_pwds(old_dir);//dizini güncellemek.
	getcwd(g_data.path, 4096);
}