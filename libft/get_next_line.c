/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:08:40 by wadina            #+#    #+#             */
/*   Updated: 2022/01/02 02:08:47 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int	gnl(int fd, char **line)
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
