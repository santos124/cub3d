#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

#define BUFFER_SIZE 3

typedef struct	s_parser {
	char	**map;
	int		col; // tebe ne nuzhno
	int		line; // tebe ne nuzhno
	int		color_bot_ceil[2][3]; //color_bot_ceil[0] - zvet pola,
	// color_bot_ceil[1] - zvet potolka
	char	*path_direction[4];// [0] - NO, [1] - SO, [2] - WE, [3] - EA
	int		tex_flag[6]; // tebe ne nuzhno
	float 	x;
	float 	y;
	float	angle;
}		t_parser;


size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}


void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
		((unsigned char *)b)[i++] = c;
	return (b);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (src > dst)
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else if (src < dst)
	{
		while (len-- > 0)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	}
	return (dst);
}

char	*ft_strjoi(char *s1, char *s2, size_t s2len)
{
	char	*s3;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + s2len + 1));
	if (s3 == NULL)
		return (NULL);
	ft_memset(s3, 0, ft_strlen(s1) + s2len + 1);
	ft_memmove(s3, s1, ft_strlen(s1));
	ft_memmove(&(s3[ft_strlen(s1)]), s2, s2len);
	s3[ft_strlen(s1) + s2len] = '\0';
	free(s1);
	s1 = NULL;
	return (s3);
}

int	ft_index(char *s, char c)
{
	int		i;
	int		len;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	buf_change(char *ptr)
{
	int	ind;
	int	len;

	len = ft_strlen(ptr);
	ind = ft_index(ptr, '\n');
	if (ind != -1 && len > ind + 1)
	{
		ft_memmove(ptr, &((ptr)[ind + 1]), len - ind - 1);
		ptr[len - ind - 1] = 0;
	}
	else
		ptr[0] = 0;
}

void	next_line(char *bf, char **line, int fd, int *ret)
{
	while (*ret > 0)
	{
		if (ft_strlen(bf) == 0)
		{
			*ret = read(fd, bf, BUFFER_SIZE);
			bf[*ret] = 0;
		}
		*ret = ft_strlen(bf);
		if (*ret < 1)
		{
			*line = ft_strjoi(*line, bf, *ret);
			break ;
		}
		if (ft_index(bf, '\n') == -1)
		{
			*line = ft_strjoi(*line, bf, *ret);
			bf[0] = 0;
		}
		else
		{
			*line = ft_strjoi(*line, bf, ft_index(bf, '\n'));
			break ;
		}
	}
}

int	get_next_line(int fd, char **line)
{
	static char		buf[BUFFER_SIZE + 1];
	int				ret;

	if (!line || fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (-1);
	*line = malloc(1);
	(*line)[0] = 0;
	ret = 1;
	next_line(buf, line, fd, &ret);
	buf_change(buf);
	if (ret == 0)
		return (0);
	return (1);
}

t_parser	*ft_init_struct(t_parser *p)
{
	p = (t_parser *)malloc(sizeof(t_parser) * 1);
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

static void	check_valid_char(t_parser *p)
{
	int i;
	int j;
	int	dup;

	dup = 0;
	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] != 'N' && p->map[i][j] != 'S' && p->map[i][j] != 'W' &&
				p->map[i][j] != 'E' && p->map[i][j] != '1' && p->map[i][j] != '0' &&
				p->map[i][j] != ' ')
				return (ft_error("Error: invalid characters detected!", p));
			if (p->map[i][j] == 'N' || p->map[i][j] == 'S' || p->map[i][j] == 'W' ||
				p->map[i][j] == 'E')
				dup++;
			if (dup > 1)
				return (ft_error("Error: repeatable characters detected!", p));
			j++;
		}
		i++;
	}
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}


void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	arr = malloc(count * size);
	if (arr == NULL)
		return (arr);
	ft_bzero(arr, count * size);
	return (arr);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (NULL == s2)
		return (NULL);
	ft_memmove(s2, s1, ft_strlen(s1));
	return (s2);
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
				ft_error("Error: malloc error!", NULL);
		}
		else
			new[i] = NULL;
		i++;
	}
	new[i] = NULL;
	while (j--)
		free(map[j]);
	free(map);
	return (new);
}

static void parse_map(t_parser *p, int fd)
{
	char	*buf;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while(k < 2)
	{
		if (!get_next_line(fd, &buf))
			k++;
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
		p->map[i] = ft_strdup(buf);
		if (!p->map[i])
			ft_error("Error: malloc error!", p);
		i++;
		free(buf);
	}
	free(buf);
	close(fd);
}


static void	player_look(int i, int j, t_parser *p) // S N
{
	p->x = j + 0.5;
	p->y = i + 0.5;
	if (p->map[i][j] == 'S')
		p->angle = M_PI / 2;
	if (p->map[i][j] == 'N')
		p->angle = 3 * M_PI / 2;
	if (p->map[i][j] == 'E')
		p->angle = M_PI;
	if (p->map[i][j] == 'W')
		p->angle = 0;
}

void parse_player(t_parser *p)
{
	int	i;
	int	j;

	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] == 'E' || p->map[i][j] == 'W'
				|| p->map[i][j] == 'S' || p->map[i][j] == 'N')
			{
				player_look(i, j, p);
				return ;
			}
			j++;
		}
		i++;
	}
	ft_error("Error: no player on the map!", p);
}

static void	check_map_size(t_parser *p)
{
	int		i;
	int		j;

	i = 0;
	while (p->map[i])
	{
		j = 0;
		while (p->map[i][j])
		{
			j++;
			if (j > p->line)
				p->line = j;
		}
		i++;
	}
	p->col = i;
}

static char	*ft_realloc_mod(char *str, int num, char c)
{
	int i;
	char *new;

	i = 0;
	new = (char *)malloc(sizeof(char) * (num + 1));
	if (!new)
		ft_error("Error: malloc error!", NULL);
	new = (char *)ft_memset(new, ' ', num);
	new[num] = '\0';
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	while (i < num)
	{
		new[i] = c;
		i++;
	}
	return (new);
}

void	rectangle_map(t_parser *p)
{
	int	i;


	i = 0;
	check_map_size(p);
	while (p->map[i])
	{
		if ((int)ft_strlen(p->map[i]) < p->line)
		{
			p->map[i] = ft_realloc_mod(p->map[i], p->line, ' '); // \0
			// dopolnitelno
			if (p->map[i] == NULL)
				ft_error("Error: malloc error!", p);
		}
		i++;
	}
}

static int	check_line(t_parser *p) // 0 error; 1 norm map
{
	int i;
	int j;
	int last;

	i = 0;
	last = 0;
	while (i < p->col)
	{
		j = 0;
		while (j < p->line && p->map[i][j] == ' ')
			j++;
		if (j < p->line && p->map[i][j] != '1')
			return (0); // false
		j++;
		while (j < p->line)
		{
			if (p->map[i][j] == '1')
				last = 1;
			if (p->map[i][j] == '0')
				last = 0;
			if (p->map[i][j] == ' ' && last == 0)
				return (0); // false
			if (p->map[i][j - 1] == ' ' && p->map[i][j] == '0')
				return (0); //false
			j++;
		}
		if (last != 1)
			return (0); // false
		i++;
	}
	return (1); // norm
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
			return (0); // false
		i++;
		while (i < p->col)
		{
			if (p->map[i][j] == '1')
				last = 1;
			if (p->map[i][j] == '0')
				last = 0;
			if (p->map[i][j] == ' ' && last == 0)
				return (0); // false
			if (p->map[i-1][j] == ' ' && p->map[i][j] == '0')
				return (0); //false
			i++;
		}
		if (last != 1)
			return (0); // false
		j++;
	}
	return (1); // norm
}

int		check_walls(t_parser *p)
{
	if (!check_line(p))
		return (0);
	if (!check_column(p))
		return (0);
	return (1);
}


static void	free_all(char **all)
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

static int	get_texture(int type, char *buf, t_parser *p) //file zavesti
{
	int	i;

	i = 0;
	while (buf[i] == ' ')
		i++;
	p->path_direction[type] = ft_strdup(buf + i);
	if (!p->path_direction[type])
		ft_error("Error: malloc error!", p);
	p->tex_flag[type] += 1; //flag
//	fd = open(file, O_RDONLY); // otkomentit
//	if (fd == -1)
//		ft_error("Error: texture file not detected!", p);
//	close(fd);
	return (0);
}





int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dst == NULL || src == NULL)
		return (0);
	while (i < dstsize - 1 && src[i] != '\0' && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

static int	ft_ok(char c)
{
	if (c == 9 || c == 10 || c == 11)
		return (2);
	else if (c == 12 || c == 13 || c == 32)
		return (2);
	else if (ft_isdigit(c))
		return (1);
	else if (c == '-' || c == '+')
		return (3);
	else
		return (5);
}

static long	ft_mult(const char *str, int i, long num, long sign)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((num * sign) < -2147483648)
			return (0);
		else if ((num * sign) > 2147483647)
			return (-1);
		else
			num = num * 10 + str[i] - '0';
		if (!(str[i + 1] >= '0' && str[i + 1] <= '9'))
			break ;
		i++;
	}
	return (num * sign);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	num;
	long	sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] && ft_ok(str[i]) < 4)
	{
		if (ft_ok(str[i]) == 3 && ft_ok(str[i + 1]) == 1)
			if (str[i] == '-')
				sign = -1;
		if (ft_ok(str[i]) == 3 && ft_ok(str[i + 1]) != 1)
			break ;
		if (ft_isdigit(str[i]))
		{
			num = ft_mult(str, i, num, sign);
			break ;
		}
		if (ft_ok(str[i]) == 2 && ft_ok(str[i + 1]) == 3)
			if (ft_ok(str[i + 2]) != 1)
				break ;
		i++;
	}
	return (num);
}



static long	ft_len(const char *s, long start, long len)
{
	long int	i;

	i = start;
	while ((s[i] != 0) && i < (len + start))
		i++;
	return (i - start);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;

	if (!s)
		return (NULL);
	s2 = (char *)ft_calloc(1 + (size_t)ft_len(s, start, len), sizeof(char));
	if (NULL == s2)
		return (NULL);
	if (start >= ft_strlen(s))
		return (s2);
	ft_strlcpy(s2, &s[start], ft_len(s, start, len) + 1);
	return (s2);
}







static void	ft_liberator(char **ss, unsigned int j)
{
	while (j)
	{
		free(ss[j--]);
	}
	free(ss);
}

static int	ft_len_c(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) == c)
	{
		i++;
	}
	return (i);
}

static char	**ft_separator(char **ss, const char *s, int c)
{
	size_t	i;
	size_t	j;
	size_t	tmp;
	size_t	l;

	j = 0;
	i = 0;
	tmp = 0;
	while (i < ft_strlen(s) && ft_strlen(s) > 0)
	{
		if ((((*(s + i + 1) == c) || (*(s + i + 1) == 0)) && s[i] != c))
		{
			l = ft_len_c(&s[tmp], c);
			*(ss + j) = ft_substr(s, l + tmp, i + 1 - tmp - l);
			tmp = i + 1;
			if (ss[j] == NULL)
			{
				ft_liberator(ss, j);
				return (ss);
			}
			j++;
		}
		i++;
	}
	return (ss);
}

static int	ft_num_str(char const *s, int c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && *(s + i - 1) == c)
		{
			j++;
		}
		i++;
	}
	if (i != 0 && s[ft_strlen(s) - 1] != c && j != 0 && s[0] != c)
		j++;
	if (i != 0 && s[ft_strlen(s) - 1] != c && j == 0)
		j++;
	if (i != 0 && j == 0)
		j++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**ss;

	if (!s)
		return (NULL);
	i = ft_num_str(s, c);
	ss = (char **)ft_calloc(i + 1, sizeof(char *));
	if (ss == NULL)
		return (NULL);
	ft_separator(ss, s, c);
	return (ss);
}

static int	get_color(int type, char *buf, t_parser *p)
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
	while (buf[j])
	{
		if (buf[j] == ',')
			k++;
		j++;
	}
	if (k != 2)
		ft_error("Error: wrong RGB value!", p);
	split = ft_split(buf + i, ',');
	while (k >= 0)
	{
		color = ft_atoi(split[k]);
		if (color >= 255 || color < 0)
			ft_error("Error: wrong RGB value!", p);
		p->color_bot_ceil[type][k] = color;
		k--;
	}
	free_all(split);
	p->tex_flag[type + 4] += 1; // flag
	return (0);
}

int		parse_tex_and_colors(char *buf, t_parser *p)
{
	int	i;

	i = 0;
	if (p->tex_flag[0] > 1 || p->tex_flag[1] > 1 || p->tex_flag[2] > 1 ||
		p->tex_flag[3] > 1 || p->tex_flag[4] > 1 || p->tex_flag[5] > 1)
		ft_error("Error: repeatable symbols!", p);
	if (p->tex_flag[0] == 1 && p->tex_flag[1] == 1 && p->tex_flag[2] == 1 &&
		p->tex_flag[3] == 1 && p->tex_flag[4] == 1 && p->tex_flag[5] == 1)// check
		// massiv that only one  n s e w f c
		return (-1);
	while (buf[i] == ' ')
		i++;
	if (!strncmp("NO ", buf + i, 3))
		return (get_texture(0, buf + i + 3, p)); // check texture file errors
// handling ft_error("Error: some errors in textures and files in mapfile!");
	if (!strncmp("SO ", buf + i, 3))
		return (get_texture(1, buf + i + 3, p));
	if (!strncmp("WE ", buf + i, 3))
		return (get_texture(2, buf + i + 3, p));
	if (!strncmp("EA ", buf + i, 3))
		return (get_texture(3, buf + i + 3, p));
	if (!strncmp("F ", buf + i, 2))
		return (get_color(0, buf + i + 2, p));
	if (!strncmp("C ", buf + i, 2))
		return (get_color(1, buf + i + 2, p));
	return (0);
}

t_parser	*parse_all(char *file) //posmotret vozvrashaemoe znatschenie
{
	int			fd;
	char		*buf;
	t_parser	*p;

	p = NULL;
	buf = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Error: mapfile not detected!", p);
	p = ft_init_struct(p); // init structure parse
	while (get_next_line(fd, &buf) && !parse_tex_and_colors(buf, p))  //
		// check_read_texcol check textures and colors flags in structure parse
		free(buf);
	if (buf)
		free(buf);
	parse_map(p, fd);
	rectangle_map(p);
	if (!p->map)
		ft_error("Error: can't read map!", p);
	check_valid_char(p);
	if (!check_walls(p))
		ft_error("Error: map is not surrounded by walls!", p);
	parse_player(p);
	return (p); // posmotret vozvrashaemoe znatschenie
}

int	main(int argc, char **argv)
{
	t_parser	*p;
	int 		i;
	int			j;

	i = 0;
	p = NULL;
	if (argc != 2)
		return (1);
	p = parse_all(argv[1]);
	while (p->map[i])
		printf("%s\n", p->map[i++]);
	printf("Num_col = %d\nNum_line = %d\n", p->col, p->line);
	i = 0;
	while (i < 4)
		printf("%s\n", p->path_direction[i++]);
	i = 0;
	while (p->map[i])
		printf("%s\n", p->map[i++]);
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 3)
			printf("%d,", p->color_bot_ceil[i][j++]);
		i++;
		printf("\n");
	}
	printf("%f\n", p->x);
	printf("%f\n", p->y);
	printf("%f\n", p->angle);
	return (0);
}

char	**map;
int		col; // tebe ne nuzhno
int		line; // tebe ne nuzhno
int		color_bot_ceil[2][3]; //color_bot_ceil[0] - zvet pola,
// color_bot_ceil[1] - zvet potolka
char	*path_direction[4];// [0] - NO, [1] - SO, [2] - WE, [3] - EA
int		tex_flag[6]; // tebe ne nuzhno
float 	x;
float 	y;
float	angle;

