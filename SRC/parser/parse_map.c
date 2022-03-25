
#include "so_long.h"

//struct
typedef struct s_parse
{
	int	tex[6];
}	t_parse;

typedef struct	s_direction
{
	char	*path;
}	t_dir;

typedef struct	s_bot_ceil
{
	int	color[3];
} t_bot;

typedef	struct	s_tex
{
	t_dir	*direction;
	t_bot	*bot_ceil;

}	t_tex;


typedef	struct	s_ray
{




}	t_ray;

typedef struct s_all
{
	t_parse	*parse;
	char	**map;
	t_tex	*tex;
	t_ray	*ray;


}	t_all;




int	check_valid_char(char **map) // map
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





void	ft_init_struct(             )
{

}


int		parse_tex_and_colors(char *buf, t_tex *tex, t_parse *parse)
{
	int	i;

	i = 0;
	if (parse->tex[0] == 1 && parse->tex[1] == 1 && parse->tex[2] == 1 &&
	parse->tex[3] == 1 && parse->tex[4] == 1 && parse->tex[5] == 1)// check
	// massiv that only one  n s e w f c checked
		return (1);
	while (buf[i] == ' ')
		i++;
	if (!strncmp("NO ", buf + i, 3))
		return (get_texture(0, buf + i + 3, tex, parse)); // check texture file
		// errors
		// handling ft_error("Error: some errors in textures and files in
		// mapfile!");
	if (!strncmp("SO ", buf + i, 3))
		return (get_texture(1, buf + i + 3, tex, parse)); // check texture file
		// errors
		// handling ft_error("Error: some errors in textures and files in
		// mapfile!");
	if (!strncmp("WE ", buf + i, 3))
		return (get_texture(2, buf + i + 3, tex, parse)); // check texture file errors
		// handling ft_error("Error: some errors in textures and files in
		// mapfile!");
	if (!strncmp("EA ", buf + i, 3))
		return (get_texture(3, buf + i + 3, tex, parse)); // check texture file errors
		// handling ft_error("Error: some errors in textures and files in
		// mapfile!");
	if (!strncmp("F ", buf + i, 2))
		return (get_color(0, buf + i + 2, tex, parse)); // check texture file
		// errors
		// handling ft_error("Error: some errors in textures and files in
		// mapfile!");
	if (!strncmp("C ", buf + i, 2))
		return (get_color(1, buf + i + 2, tex, parse)); // check texture file errors
		// handling ft_error("Error: some errors in textures and files in
		// mapfile!");
	return (0);
}

int		get_texture(int type, char *buf, t_tex *tex, t_parse *parse)
//structure of
// texture need to be created
{
	int		i;

	i = 0;
	while (buf[i] == ' ')
		i++;
	tex->direction[type]->path = ft_strdup(buf + i);
	if (!tex->direction[type]->path)
		ft_error("Error: malloc error!");
	 parse->tex[type] = 1; //flag
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

int		get_color(int type, char *buf, t_tex *tex, t_parse *p)
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
		tex->bot_ceil[type]->color[k] = color;
		k--;
	}
	free_all(split);
	parse->tex[type + 4] = 1; // flag
	return (0);
}

int	parse_tex(t_all *all, char *file) // add structures parse, tex,
// all in header
{
	int fd;
	char *buf;

	fd = open(file, O_READONLY);
	if (fd == -1)
		ft_error("Error: mapfile not detected!");
	ft_init_struct(); // init structure parse
	while (get_next_line(fd, &buf) && !parse_tex_and_colors(buf, all->tex,
															all->parse))  //
		// check_read_texcol check textures and colors flags in structure parse
		free(buf);
	free(buf);


	all->map = get_map(all, fd); //
	if (!all->map)
		ft_error("Error: can't read map!");
	check_map(all); //
	check_walls(all); //
	parse_player(all);
	open_tex(all);
	return (   );
}


int		parse_map(t_all *all, int fd)
{
	char	*buf;

	while(get_next_line(fd, &buf))
	{
		if(!buf[0])
			continue ;
		all->map[i] = ft_strdup(buf);
		if (!all->map[i])
			ft_error("Error: malloc error!");
		i++;
		free(buf);
	}
	free(buf);
	close(fd);
	return (    );
}