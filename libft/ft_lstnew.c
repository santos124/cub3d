/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 06:39:39 by wadina            #+#    #+#             */
/*   Updated: 2021/05/09 06:39:40 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ls1;

	ls1 = (t_list *)malloc(sizeof(t_list));
	if (ls1 == NULL)
		return (NULL);
	(*ls1).content = content;
	(*ls1).next = NULL;
	return (ls1);
}
