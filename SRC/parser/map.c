#include "so_long.h"

// check path of textures

typedef struct	s_parser
{
	char	**map;
	int		col; //num str in column
	int		line; //num char in line
	int		color_bot_ceil[2][3];
	int		color_ceil[3];
	char	*path_direction[4];
	int		tex_flag[6];
}	t_parser; // заменяет t_all




int	check_valid_char(char **map)
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
				return (ft_error("Error: invalid characters detected!"));
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' ||
				map[i][j] == 'E')
				dup++;
			if (dup > 1)
				return (ft_error("Error: repeatable characters detected!"));
			j++;
		}
		i++;
	}
	return (0);
}

int		parse_tex_and_colors(char *buf, t_parser *p)
{
	int	i;

	i = 0;
	if (p->tex_flag[0] == 1 && p->tex_flag[1] == 1 && p->tex_flag[2] == 1 &&
		p->tex_flag[3] == 1 && p->tex_flag[4] == 1 && p->tex_flag[5] == 1)// check
		// massiv that only one  n s e w f c checked
		return (1);
	while (buf[i] == ' ')
		i++;
	if (!strncmp("NO ", buf + i, 3))
		return (get_texture(0, buf + i + 3, p)); // check texture file
	// errors
	// handling ft_error("Error: some errors in textures and files in
	// mapfile!");
	if (!strncmp("SO ", buf + i, 3))
		return (get_texture(1, buf + i + 3, p)); // check texture file
	// errors
	// handling ft_error("Error: some errors in textures and files in
	// mapfile!");
	if (!strncmp("WE ", buf + i, 3))
		return (get_texture(2, buf + i + 3, p)); // check texture file errors
	// handling ft_error("Error: some errors in textures and files in
	// mapfile!");
	if (!strncmp("EA ", buf + i, 3))
		return (get_texture(3, buf + i + 3, p)); // check texture file errors
	// handling ft_error("Error: some errors in textures and files in
	// mapfile!");
	if (!strncmp("F ", buf + i, 2))
		return (get_color(0, buf + i + 2, p)); // check texture file
	// errors
	// handling ft_error("Error: some errors in textures and files in
	// mapfile!");
	if (!strncmp("C ", buf + i, 2))
		return (get_color(1, buf + i + 2, p)); // check texture file errors
	// handling ft_error("Error: some errors in textures and files in
	// mapfile!");
	return (0);
}


int		get_texture(int type, char *buf, t_parser *p)
//structure of
// texture need to be created
{
	int		i;

	i = 0;
	while (buf[i] == ' ')
		i++;
	p->path_direction[type] = ft_strdup(buf + i);
	if (!p->path_direction[type])
		ft_error("Error: malloc error!");
	p->tex_flag[0] = 1; //flag
	return (0);
}

int		get_color(int type, char *buf, t_parser *p)
{
	int		i;
	int		j;
	int		k;
	char	**split;
	int		color;

	i = 0;
	k = 0;
	while (buf[i] == ' ')
		i++;
	j = i;
	while (!buf[j])
	{
		if (buf[j] == ',')
			k++;
		j++;
	}
	if (k != 2)
		ft_error("Error: wrong RGB value!");
	split = ft_split(buf + i, ',');
	while (k >= 0)
	{
		color = ft_atoi(split[k]);
		if (color >= 255 || color < 0)
			ft_error("Error: wrong RGB value!");
		p->color_bot_ceil[type][k] = color;
		k--;
	}
	free_all(split);
	p->tex_flag[type + 4] = 1; // flag
	return (0);
}

void	free_all(char **all)
{
	int	i;

	i = 0;
	while (all[i])
	{
		free(all[i]);
		i++;
	}
	free(all);
}

















char	**ft_super_malloc(char **map, int num)
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
				ft_error("Error: malloc error!");
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








int		parse_map(t_parser *p, int fd)
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
			ft_error("Error: malloc error!");
		i++;
		free(buf);
	}
	free(buf);
	close(fd);
	return (    );
}


void	check_map_size(t_parser *p)
{
	int		i;
	int		j;

	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[j])
		{
			if (j > p->line)
				p->line = j;
			j++;
		}
		i++;
	}
	p->col = i;
}

// добить пробелы во все строчки закончить \0

int	parse_tex(t_parser *p, char *file) // add structures parse, tex,
// all in header
{
	int fd;
	char *buf;

	fd = open(file, O_READONLY);
	if (fd == -1)
		ft_error("Error: mapfile not detected!");
	ft_init_struct(); // init structure parse
	while (get_next_line(fd, &buf) && !parse_tex_and_colors(buf, p))  //
		// check_read_texcol check textures and colors flags in structure parse
		free(buf);
	free(buf);


	p->map = get_map(p, fd); //
	if (!p->map)
		ft_error("Error: can't read map!");
	check_map(p); //
	check_walls(p); //
	parse_player(p);
	open_tex(p);
	return (   );
}