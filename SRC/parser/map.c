#include "so_long.h"

typedef struct	s_parser
{
	char	**map;
	int		col; //num str in column
	int		line; //num char in line
	int		color_bot_ceil[2][3]; //color_bot_ceil[0] - zvet pola,
	// color_bot_ceil[1] - zvet potolka
	//int		color_ceil[3];
	char	*path_direction[4];// [0] - NO, [1] - SO, [2] - WE, [3] - EA
	int		tex_flag[6];
}	t_parser;




static void	check_valid_char(char **map)
{
	int i;
	int j;
	int	dup;

	dup = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' &&
				map[i][j] != 'E' && map[i][j] != '1' && map[i][j] != '0' &&
				map[i][j] != ' ')
				return (ft_error("Error: invalid characters detected!", p));
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' ||
				map[i][j] == 'E')
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
	while (i < num)
	{
		if (map[i])
		{
			new[i] = ft_strdup(map[i]);
			j = i;
			if (!new[i])
				ft_error("Error: malloc error!", p);
		}
		else
			new[i] = NULL;
		i++;
	}
	new[i] = NULL;
	while (j--)
		free(map[j]);
	free(map);
	return (new)
}

static void parse_map(t_parser *p, int fd)
{
	char	*buf;
	int		i;

	i = 0;
	while(get_next_line(fd, &buf))
	{
		if(!buf[0])
			continue ;
		if (i == 0)
		{
			p->map = (char **)malloc(sizeof(char *) * 2);
			p->map[0] = ft_strdup(buf);
			p->map[1] = NULL;
			i++;
			continue;
		}
		p->map = ft_super_malloc(p->map, i + 1);
		p->map[i] = ft_strdup[buf];
		if (!p->map[i])
			ft_error("Error: malloc error!", p);
		i++;
		free(buf);
	}
	free(buf);
	close(fd);
}


int		parse_all(char *file) //posmotret vozvrashaemoe znatschenie
{
	int			fd;
	char		*buf;
	t_parser	*p;

	fd = open(file, O_READONLY);
	if (fd == -1)
		ft_error("Error: mapfile not detected!", p);
	p = ft_init_struct(p); // init structure parse
	while (get_next_line(fd, &buf) && !parse_tex_and_colors(buf, p))  //
		// check_read_texcol check textures and colors flags in structure parse
		free(buf);
	free(buf);
	parse_map(p, fd);
	rectangle_map(p);
	if (!p->map)
		ft_error("Error: can't read map!", p);
	check_valid_char(p->map);
	if (!check_walls(p))
		ft_error("Error: map is not surrounded by walls!", p);
	parse_player(p);
	return (0); // posmotret vozvrashaemoe znatschenie
}
