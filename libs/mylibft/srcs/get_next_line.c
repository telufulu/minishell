/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telufulu <telufulu@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:45:23 by telufulu          #+#    #+#             */
/*   Updated: 2023/12/22 17:20:55 by telufulu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_buffer(int fd, char **store)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*aux;
	int		rd;

	rd = 0;
	while (rd < BUFFER_SIZE)
		buffer[rd++] = 0;
	rd = 1;
	while (rd > 0 && !ft_strchr(buffer, '\n'))
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd < 0)
			return (-1);
		if (!rd)
			return (0);
		buffer[rd] = 0;
		aux = (*store);
		(*store) = ft_strjoin((*store), buffer);
		free(aux);
		if (!(*store))
			return (-1);
	}
	return (0);
}

static char	*get_line(char **store)
{
	size_t	len;
	size_t	i;
	char	*res;
	char	*aux;

	len = 0;
	i = -1;
	aux = 0;
	if (!(*store)[len])
		return (NULL);
	while ((*store)[len] && (*store)[len] != '\n')
		len++;
	if ((*store)[len] == '\n')
		len++;
	res = ft_calloc(sizeof(char), len + 1);
	if (!res)
		return (NULL);
	while ((*store)[++i] && i < len)
		res[i] = (*store)[i];
	aux = (*store);
	(*store) = ft_strdup((*store) + len);
	if (!(*store))
		return (free(aux), free(res), NULL);
	return (free(aux), res);
}

void	*del(char **s)
{
	free((*s));
	(*s) = 0;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*store[MAX_FD];
	char		*res;
	int			aux;

	res = 0;
	aux = 0;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!store[fd] || (*store[fd] && !ft_strchr(store[fd], '\n')))
		aux = get_buffer(fd, &store[fd]);
	if (aux < 0 || !store[fd])
		return (del(&store[fd]));
	if (store[fd] && *store[fd])
		res = get_line(&store[fd]);
	if (!res)
		return (del(&store[fd]));
	if (store[fd] && !*store[fd])
		del(&store[fd]);
	return (res);
}
