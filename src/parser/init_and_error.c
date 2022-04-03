/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:10:43 by eaurelio          #+#    #+#             */
/*   Updated: 2022/04/02 23:10:46 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_parser	*ft_init_struct(t_parser *p)
{
	p = (t_parser *)malloc(sizeof(t_parser) * 1);
	if (!p)
		ft_error("Error: malloc error!", p);
	*p = (t_parser){0};
	return (p);
}

void	ft_error(char *info, t_parser *p)
{
	int	i;

	i = 0;
	if (p)
	{
		while (i < 4)
		{
			if (p->path_direction[i])
				free(p->path_direction[i]);
			i++;
		}
		if (p->map)
		{
			i = 0;
			while (p->map[i])
			{
				free(p->map[i]);
				i++;
			}
			free(p->map);
		}
		free(p);
	}
	printf("%s\n", info);
	exit(1);
}
