#include "../cub3d.h"

static void	check_valid_char(t_parser *p)
{
	int	i;
	int	j;
	int	dup;

	dup = 0;
	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] != 'N' && p->map[i][j] != 'S' &&
				p->map[i][j] != 'W' && p->map[i][j] != 'E' &&
				p->map[i][j] != '1' && p->map[i][j] != '0' &&
				p->map[i][j] != ' ')
				return (ft_error("Error: invalid characters detected!", p));
			if (p->map[i][j] == 'N' || p->map[i][j] == 'S' ||
				p->map[i][j] == 'W' || p->map[i][j] == 'E')
				dup++;
			if (dup > 1)
				return (ft_error("Error: repeatable characters detected!", p));
			j++;
		}
		i++;
	}
}

static char	**ft_super_malloc(char **map, int num)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * (num + 1));
	if (new == NULL)
		ft_error("Error: malloc error!", NULL);
	while (i < num)
	{
		if (map[i])
		{
			new[i] = ft_strdup(map[i]);
			j = i;
			if (!new[i])
				ft_error("Error: malloc error!", NULL);
		}
		else
			new[i] = NULL;
		i++;
	}
	new[i] = NULL;
	while (j >= 0)
		free(map[j--]);
	free(map);
	return (new);
}

//static void	sub_parse_map(t_parser *p, char *buf, int *i)
//{
//	p->map = (char **)malloc(sizeof(char *) * 2);
//	if (!p->map)
//		ft_error("Error: malloc error!", p);
//	p->map[0] = ft_strdup(buf);
//	p->map[1] = NULL;
//	(*i)++;
//}

static int 	check_parse_flags(t_parser *p)
{
	if (p->tex_flag[0] == 1 && p->tex_flag[1] == 1 && p->tex_flag[2] == 1 &&
		p->tex_flag[3] == 1 && p->tex_flag[4] == 1 && p->tex_flag[5] == 1)
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


static void	parse_map(t_parser *p, int fd)
{
	char 	*buf;
	int		i;
	int 	ret;

	i = 0;
	ret = 1;
	ret = gnl(fd, &buf);
	while (ret != 0 && !buf[0])
	{
		free (buf);
		ret = gnl(fd, &buf);
	}
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
	if (fd == -1)
		ft_error("Error: mapfile not detected!", p);
	p = ft_init_struct(p);
	while (gnl(fd, &buf) && !parse_tex_and_colors(buf, p))
	{
		if (check_parse_flags(p) == -1)
			break ;
		free (buf);
	}
	free (buf);
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
