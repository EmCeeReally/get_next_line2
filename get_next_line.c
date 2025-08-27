/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yudedele <yudedele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:53:05 by yudedele          #+#    #+#             */
/*   Updated: 2025/08/27 16:39:38 by yudedele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_return(void *p1)
{
	if (p1)
		free(p1);
	return (NULL);
}

static char	*gn_get_line(char *s1)
{
	char	*line;
	int		i;

	i = 0;
	if (!s1 || s1[0] == '\0')
		return (NULL);
	while (s1[i] && s1[i] != '\n')
		i++;
	if (s1[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = -1;
	while (s1[++i] && s1[i] != '\n')
		line[i] = s1[i];
	if (s1[i] == '\n')
	{
		line[i] = s1[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*gn_get_remaining(char *s1)
{
	char	*remaining;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] != '\n')
		i++;
	if (!s1[i])
	{
		free(s1);
		return (NULL);
	}
	i++;
	remaining = malloc(gn_len(s1) - i + 1);
	if (!remaining)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i])
		remaining[j++] = s1[i++];
	remaining[j] = '\0';
	free(s1);
	return (remaining);
}

static char	*read_and_join(int fd, char *s1)
{
	char	*buffer;
	int		b_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	b_read = 1;
	while (!gn_chr(s1, '\n') && b_read != 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
		{
			free(s1);
			free(buffer);
			return (NULL);
		}
		buffer[b_read] = '\0';
		s1 = gn_strjoin(s1, buffer);
		if (!s1)
			return (ft_return(buffer));
	}
	free(buffer);
	return (s1);
}

char	*get_next_line(int fd)
{
	static char	*s1;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s1 = read_and_join(fd, s1);
	if (!s1 || s1[0] == '\0')
	{
		free(s1);
		s1 = NULL;
		return (NULL);
	}
	line = gn_get_line(s1);
	s1 = gn_get_remaining(s1);
	return (line);
}
#include <fcntl.h>
#include <stdio.h> 
int main()
{
	int fd = open("test.txt",O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s",line);
	free(line);
	close(fd);
}