/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:56:58 by eaurelio          #+#    #+#             */
/*   Updated: 2022/04/02 23:57:00 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_parse_flags(t_parser *p)
{
	if (p->tex_flag[0] == 1 && p->tex_flag[1] == 1 && p->tex_flag[2] == 1
		&& p->tex_flag[3] == 1 && p->tex_flag[4] == 1 && p->tex_flag[5] == 1)
		return (-1);
	return (0);
}

static void	sub_parse_map(t_parser *p, char *buf)
{
	p->map = (char **)malloc(sizeof(char *) * 2);
	if (!p->map)
		ft_error("Error: malloc error!", p);
	p->map[0] = ft_strdup(buf);
	p->map[1] = NULL;
}

static void	gnl_parse_map(int fd, int *ret, char **buf)
{
	*ret = gnl(fd, buf);
	while (*ret != 0 && !(*buf)[0])
	{
		free (*buf);
		*ret = gnl(fd, buf);
	}
}

static void	parse_map(t_parser *p, int fd)
{
	char	*buf;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	gnl_parse_map(fd, &ret, &buf);
	while (ret && buf[0])
	{
		if (i == 0)
		{
			sub_parse_map(p, buf);
			i++;
			continue ;
		}
		free(buf);
		ret = gnl(fd, &buf);
		p->map = ft_super_malloc(p->map, i + 1);
		p->map[i] = ft_strdup(buf);
		if (!p->map[i++])
			ft_error("Error: malloc error!", p);
	}
	free (buf);
	close(fd);
}

t_parser	*parse_all(char *file)
{
	int			fd;
	char		*buf;
	t_parser	*p;

	p = NULL;
	buf = NULL;
	fd = open(file, O_RDONLY);
	check_map_format(file, &fd);
	p = ft_init_struct(p);
	while (gnl(fd, &buf) && !parse_tex_and_colors(buf, p))
	{
		free (buf);
		if (check_parse_flags(p) == -1)
			break ;
	}
	parse_map(p, fd);
	rectangle_map(p);
	if (!p->map)
		ft_error("Error: can't read map!", p);
	check_valid_char(p);
	if (!check_walls(p))
		ft_error("Error: map error!", p);
	parse_player(p);
	return (p);
}
