/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:10:06 by rchampli          #+#    #+#             */
/*   Updated: 2022/03/23 16:27:22 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_home_path(char *path, char **envp)
{
	char	*tmp;
	char	*tmpp;

	if (!ft_strncmp(path, "~/", 2))
	{
		tmp = get_env("HOME", envp);
		if (tmp)
		{
			tmpp = ft_substr(path, 1, ft_strlen(path));
			free(path);
			path = ft_strjoin(tmp, tmpp);
			free(tmpp);
			free(tmp);
			return (path);
		}
	}
	return (path);
}

int	change(char *path, int home, char **envp)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env("OLDPWD", pwd, envp);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env("PWD", pwd, envp);
			free(pwd);
		}
		if (home)
			free(path);
		return (1);
	}
	free(pwd);
	return (0);
}

int	set_directory(char *path, int home, char **envp)
{
	struct stat	st;

	if (change(path, home, envp))
		return (1);
	dup2(STDOUT_FILENO, STDERR_FILENO);
	printf("minishell: cd: ");
	printf("%s", path);
	if (stat(path, &st) == -1)
		printf(": No such file or directory");
	else if (!(st.st_mode & S_IXUSR))
		printf(": Permission denied");
	else
		printf(": Not a directory");
	printf("\n");
	if (home)
		free(path);
	return (1);
}

int	s_path(char **av, char **envp)
{
	char	*tmp;

	if (ft_strequ(av[1], "-"))
	{
		tmp = get_env("OLDPWD", envp);
		if (tmp)
		{
			set_directory(tmp, 0, envp);
			free(tmp);
		}
		tmp = get_env("PWD", envp);
		if (tmp)
		{
			printf("%s", tmp);
			free(tmp);
		}
		return (1);
	}
	return (set_directory(av[1], 0, envp));
}

int	cd(char **av, char **envp)
{
	char	*home;

	home = NULL;
	if (av && av[1] && av[2])
	{
		dup2(STDOUT_FILENO, STDERR_FILENO);
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (!av || ft_strequ(av[1], "~") || ft_strequ(av[1], "--"))
	{
		home = get_env("HOME", envp);
		if (!home)
		{
			dup2(STDOUT_FILENO, STDERR_FILENO);
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		return (set_directory(home, 1, envp));
	}
	av[1] = add_home_path(av[1], envp);
	return (s_path(av, envp));
}
