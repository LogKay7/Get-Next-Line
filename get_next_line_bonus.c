/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkailany <lkailany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:41:35 by lkailany          #+#    #+#             */
/*   Updated: 2022/02/09 10:02:26 by lkailany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_to_newline(int fd, char *linejoined)
{
	char	*buff;
	int		sizeread;

	buff = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	sizeread = 1;
	while (!ft_strchr(linejoined, '\n') && sizeread != 0)
	{
		sizeread = read(fd, buff, BUFFER_SIZE);
		if (sizeread == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[sizeread] = '\0';
		linejoined = ft_strjoin(linejoined, buff);
	}
	free(buff);
	return (linejoined);
}

char	*ft_save_endline(char *linejoined)
{
	char	*newbuff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (linejoined[i] != '\0' && linejoined[i] != '\n')
		i++;
	if (linejoined[i] == '\0')
	{
		free(linejoined);
		return (NULL);
	}
	newbuff = malloc(ft_strlen(linejoined) - i + 1);
	if (!newbuff)
		return (NULL);
	i++;
	while (linejoined[i])
	{
		newbuff[j] = linejoined[i++];
		j++;
	}
	newbuff[j] = '\0';
	free(linejoined);
	return (newbuff);
}

char	*get_next_line(int fd)
{
	static char	*linejoined[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	linejoined[fd] = ft_read_to_newline(fd, linejoined[fd]);
	if (!linejoined[fd])
		return (NULL);
	line = ft_splitline(linejoined[fd]);
	linejoined[fd] = ft_save_endline(linejoined[fd]);
	return (line);
}
