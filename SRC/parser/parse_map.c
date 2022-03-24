
#include "so_long.h"

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
				return (ft_error("Error: invalid characters detected!")); //
				// ft_error!!!!!
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


int	parse_textures_and_colors(          )
{
	if ( )// check structure that only one  n w s e bot ceil
		return (1);
	if (!strncmp("NO ", buf, 3))
		return (get_texture  ); // check texture file errors handling ft_error("Error: some errors in textures and files in mapfile!");
	if (!strncmp("SO ", buf, 3))
		return (get_texture  ); // check texture file errors handling ft_error("Error: some errors in textures and files in mapfile!");
	if (!strncmp("WE ", buf, 3))
		return (get_texture  ); // check texture file errors handling ft_error("Error: some errors in textures and files in mapfile!");
	if (!strncmp("EA ", buf, 3))
		return (get_texture  ); // check texture file errors handling ft_error("Error: some errors in textures and files in mapfile!");
	if (!strncmp("F ", buf, 2))
		return (get_color  ); // check texture file errors handling ft_error("Error: some errors in textures and files in mapfile!");
	if (!strncmp("C ", buf, 2))
		return (get_color  ); // check texture file errors handling ft_error("Error: some errors in textures and files in mapfile!");
	return (0);
}

int		get_texture(int type, char *buf, t_tex *tex, t_parse *p) //structure of
// texture
// need to be
// created
{
	int		i;
	int		j;

	i = 0;
	while (buf[i] != ' ')
		i++;
	i++;
	tex->direction[type]->path = ft_strdup(buf + i);
	if (!tex->direction[type]->path)
		ft_error("Error: malloc error!");
	 parse->tex[type] = 1;
	 return (0);
}










int	parse_text_file(t_parse parse, char *filename) // add structure parse in
// header
{
	int fd;
	char *buf;

	fd = open(filename, O_READONLY);
	if (fd == -1)
		ft_error("Error: mapfile not detected!");
	ft_init_struct(); // init structure parse
	while (get_next_line(fd, &buf) && !parse_textures_and_colors(    ))  //
		// check_read_texcol check textures and colors flags in structure parse
		free(buf);
	free(buf);
	while  // parse map


	return (   );
}
