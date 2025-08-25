/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yudedele <yudedele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:53:05 by yudedele          #+#    #+#             */
/*   Updated: 2025/08/25 17:53:06 by yudedele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_return(void *p1, void *p2, void *p3, void *p4)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	if (p4)
		free(p4);
	return (NULL);
}

char	*gn_get_line(char *s1)
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

char	*gn_get_remaining(char *s1)
{
	char	*remaining;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] != '\n')
		i++;
	if (!s1[i])
		return (ft_return(s1, NULL, NULL, NULL));
	i++;
	remaining = malloc(gn_len(s1) - i + 1);
	if (!remaining)
		return (ft_return(s1, NULL, NULL, NULL));
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
			return (ft_return(s1, buffer, NULL, NULL));
		buffer[b_read] = '\0';
		s1 = gn_strjoin(s1, buffer);
		if (!s1)
			return (ft_return(buffer, NULL, NULL, NULL));
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
		return (free(s1), s1 = NULL, NULL);
	line = gn_get_line(s1);
	s1 = gn_get_remaining(s1);
	return (line);
}
