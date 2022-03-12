/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:50:16 by manuel            #+#    #+#             */
/*   Updated: 2022/03/12 02:59:59 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/resource.h>

#include <stdio.h>

static char	*ft_straddc(char *s, char c)
{
	char	*s_new;
	int		len;

	if (s)
		len = ft_strlen(s);
	else
		len = 0;
	s_new = malloc(len + 2);
	if (!s_new)
		return (NULL);
	if (s)
	{
		ft_memcpy(s_new, s, len);
		free(s);
	}
	s_new[len] = c;
	s_new[len + 1] = 0;
	return (s_new);
}

int	get_next_line(int fd, char **line)
{
	int		nb;
	char	c;

	if (fd < 0 || fd >= RLIMIT_NOFILE || !line)
		return (-1);
	*line = ft_strdup("");
	if (!*line)
		return (-1);
	while (1)
	{
		nb = read(fd, &c, 1);
		if (nb <= 0 || c == '\n')
			break ;
		*line = ft_straddc(*line, c);
	}
	return (nb);
}

/*
static int	gnl_file(int fd, char **str, char *buf)
{
	ssize_t	size;
	char	*tmp;

	printf("DEBUG: gnl_file\n");
	size = read(fd, buf, BUFFER_SIZE);
	if (size < 1)
		return (size);
	buf[size] = '\0';
	if (!str[fd])
		str[fd] = ft_strdup(buf);
	else
	{
		tmp = ft_strjoin(str[fd], buf);
		free(str[fd]);
		str[fd] = tmp;
	}
	if (!str[fd])
		return (-1);
	return (1);
}

static int	gnl_set_line(int fd, char **str, char **line, char *end)
{
	char	*tmp;

	if (end)
	{
		tmp = ft_strdup(end + 1);
		*end = '\0';
		*line = ft_strdup(str[fd]);
		free(str[fd]);
		str[fd] = tmp;
		return (1);
	}
	else if (str[fd])
	{
		*line = ft_strdup(str[fd]);
		free(str[fd]);
		str[fd] = NULL;
	}
	else
		*line = ft_strdup("\0");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*str[OPEN_MAX];
	int			status;
	char		*buf;
	char		*end;

	if (!line || BUFFER_SIZE < 1 || fd < 0 || fd > OPEN_MAX)
		return (-1);
	buf = (char *)malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	status = 1;
	// printf("DEBUG: get_next_line\n");
	// printf("DEBUG: str: %s\n", str[fd]);
	// printf("DEBUG: fd: %d\n", fd);
	// ft_strchr(str[fd], '\n');
	// *str[fd] &&
	while (!ft_strchr(str[fd], '\n') && status == 1)
		status = gnl_file(fd, str, buf);
	free(buf);
	if (status != -1)
	{
		end = ft_strchr(str[fd], '\n');
		status = gnl_set_line(fd, str, line, end);
	}
	return (status);
}
*/
