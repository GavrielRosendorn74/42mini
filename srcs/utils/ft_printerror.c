/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grosendo <grosendo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:55:57 by grosendo          #+#    #+#             */
/*   Updated: 2022/03/22 10:49:02 by grosendo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_printerror(char *s)
{
	if (!s)
		return (0);
	write(STDERR_FILENO, s, ft_strlen(s));
	return (ft_strlen(s));
}
