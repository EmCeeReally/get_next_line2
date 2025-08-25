/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yudedele <yudedele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:53:11 by yudedele          #+#    #+#             */
/*   Updated: 2025/08/25 17:53:12 by yudedele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <stdlib.h>
# include <unistd.h>

char	*gn_strjoin(char *s1, char *s2);
char	*gn_chr(const char *s, int c);
size_t	gn_len(const char *s);
char	*gn_get_line(char *s1);
char	*gn_get_remaining(char *s1);
char	*get_next_line(int fd);
#endif