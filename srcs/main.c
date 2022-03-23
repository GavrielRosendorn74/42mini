/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:40:06 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/23 20:15:47 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char**argv, char **envp)
{
	t_shell minishell;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	minishell.exit_status = 0;
	minishell.envp = realloc_env(get_env_count(envp), envp, 0);
	loop(&minishell);
	free_shell(&minishell);
	printf("exit\n");
	return (0);
}