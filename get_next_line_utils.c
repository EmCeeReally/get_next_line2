/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yudedele <yudedele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:53:03 by yudedele          #+#    #+#             */
/*   Updated: 2025/08/25 17:53:04 by yudedele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

size_t	gn_len(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*gn_chr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*gn_strjoin(char *s1, char *s2)
{
	char	*res;
	int		a;
	int		b;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	res = malloc(gn_len(s1) + gn_len(s2) + 1);
	if (!res)
		return (NULL);
	a = -1;
	while (s1[++a])
		res[a] = s1[a];
	b = 0;
	while (s2[b])
		res[a++] = s2[b++];
	res[a] = '\0';
	free(s1);
	return (res);
}
