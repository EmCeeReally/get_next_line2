/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yudedele <yudedele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:53:05 by yudedele          #+#    #+#             */
/*   Updated: 2025/08/29 23:49:34 by yudedele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

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
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		line[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';

    return line;
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
	remaining = malloc(gn_strlen(s1) - i + 1);
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

static char	*read_and_join(int fd, char *s1)//emrecan n
{
	char	*tmp;
	int		a;

	a = 1;
	while (!gn_strchr(s1, '\n') && a != 0)
	{
		tmp = malloc(BUFFER_SIZE + 1);
		if (!tmp)
			return (NULL);
		a = read(fd, tmp, BUFFER_SIZE);
		if (a == -1)
		{
			free(tmp);
			free(s1);
			return(NULL);
		}
		tmp[a] = '\0';
		s1 = gn_strjoin(s1, tmp);
		free(tmp);
	}
	return (s1);
}

char	*get_next_line(int fd)//emrecan n
{
	static char	*s1 = NULL;
	char		*line ;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s1 = read_and_join(fd, s1);
	if(!s1)
		return(NULL);
	line = gn_get_line(s1);
	s1 = gn_get_remaining(s1);
	return(line);
}
#include <stdio.h>
#include <fcntl.h>
int main()
{
	int fd; 
	char *line;
	fd = open("test.txt",O_RDONLY);
	line = get_next_line(fd);
	printf("%s",line);
	free(line);
	close(fd);
}