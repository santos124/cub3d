/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:56:41 by eaurelio          #+#    #+#             */
/*   Updated: 2022/04/02 23:56:43 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	sub_check_line(t_parser *p, int *i, int *j, int *last)
{
	if (p->map[*i][*j] == '1')
	{
		*last = 1;
		return (1);
	}
	else if (p->map[*i][*j] == '0')
	{
		*last = 0;
		return (1);
	}
	else if (p->map[*i][*j] == 'W' || p->map[*i][*j] == 'E'
		|| p->map[*i][*j] == 'N' || p->map[*i][*j] == 'S')
	{
		*last = 0;
		return (1);
	}
	else if (p->map[*i][*j] == ' ' && last == 0)
		return (0);
	else if (p->map[*i][*j - 1] == ' ' && p->map[*i][*j] == '0')
		return (0);
	return (1);
}

static int	check_line(t_parser *p)
{
	int	i;
	int	j;
	int	last;

	i = 0;
	last = 0;
	while (i < p->col)
	{
		j = 0;
		while (j < p->line && p->map[i][j] == ' ')
			j++;
		if (j < p->line && p->map[i][j] != '1')
			return (0);
		j++;
		while (j < p->line)
		{
			if (!sub_check_line(p, &i, &j, &last))
				return (0);
			j++;
		}
		if (last != 1)
			return (0);
		i++;
	}
	return (1);
}

static int	sub_check_column(t_parser *p, int *i, int *j, int *last)
{
	if (p->map[*i][*j] == '1')
	{
		*last = 1;
		return (1);
	}
	else if (p->map[*i][*j] == '0')
	{
		*last = 0;
		return (1);
	}
	else if (p->map[*i][*j] == 'W' || p->map[*i][*j] == 'E'
		|| p->map[*i][*j] == 'N' || p->map[*i][*j] == 'S')
	{
		*last = 0;
		return (1);
	}
	else if (p->map[*i][*j] == ' ' && *last == 0)
		return (0);
	else if (p->map[*i - 1][*j] == ' ' && p->map[*i][*j] == '0')
		return (0);
	return (1);
}

static int	check_column(t_parser *p)
{
	int	i;
	int	j;
	int	last;

	j = 0;
	last = 0;
	while (j < p->line)
	{
		i = 0;
		while (i < p->col && p->map[i][j] == ' ')
			i++;
		if (i < p->col && p->map[i][j] != '1')
			return (0);
		i++;
		while (i < p->col)
		{
			if (!sub_check_column(p, &i, &j, &last))
				return (0);
			i++;
		}
		if (last != 1)
			return (0);
		j++;
	}
	return (1);
}

int	check_walls(t_parser *p)
{
	if (!check_line(p))
		return (0);
	if (!check_column(p))
		return (0);
	return (1);
}
