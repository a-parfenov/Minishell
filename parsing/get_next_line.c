/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:15:45 by teusebio          #+#    #+#             */
/*   Updated: 2022/01/13 20:52:13 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_read_from_fd(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes <= 0)
		return (NULL);
	buffer[bytes] = 0;
	return (ft_strdup(buffer));
}

static char	*combine(char **s_res)
{
	char	*str;
	char	*point;
	char	*tmp;

	if (ft_strlen(*s_res) == 0)
	{
		free(*s_res);
		*s_res = NULL;
		return (NULL);
	}
	point = ft_strchr(*s_res, '\n');
	if (!point)
	{
		str = ft_strdup(*s_res);
		free(*s_res);
		*s_res = NULL;
		return (str);
	}
	*point = '\0';
	str = ft_strjoin(*s_res, "\n");
	point++;
	tmp = *s_res;
	*s_res = ft_strdup(point);
	free(tmp);
	return (str);
}

static void	concatenator(char **s_res, int fd)
{
	char	*tmp;
	char	*str;

	while (!ft_strchr(*s_res, '\n'))
	{
		str = ft_read_from_fd(fd);
		tmp = *s_res;
		if (!str)
			break ;
		else
			*s_res = ft_strjoin(*s_res, str);
		free(tmp);
		free(str);
	}
}

char	*get_next_line(int fd)
{
	static char	*s_res = NULL;

	if (fd < 0)
		return (NULL);
	if (!s_res)
	{
		s_res = ft_read_from_fd(fd);
		if (!s_res)
			return (NULL);
	}
	concatenator(&s_res, fd);
	return (combine(&s_res));
}
