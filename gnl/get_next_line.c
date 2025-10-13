/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 02:24:24 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/12 21:32:54 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	unsigned char	a = (unsigned char) c;
	while (s && *s && *s != a)
		s++;
	return (s && *s == a ? s : 0);
}

char	*ft_strdup(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	char *dst = malloc(i + 1);
	i = -1;
	while (s[++i])
		dst[i] = s[i];
	dst[i] = 0;
	return dst;
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	len1 = 0, len2 = 0, i = 0, j = 0;
	while (s1 && s1[len1])
		len1++;
	while (s2 && s2[len2])
		len2++;
	char	*dst = malloc(len1 + len2 + 1);
	while (i < len1)
		dst[i++] = *s1++;
	while (j < len2)
		dst[i + j++] = *s2++;
	dst[i + j] = 0;
	return dst;
}

void	*free_stash(char *s)
{
	free(s);
	s = 0;
	return 0;
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	char		*line, *tmp;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return 0;
	i = 1;
	while (!ft_strchr(stash, 10) && i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i <= 0)
			break;
		buffer[i] = 0;
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		stash = tmp;
	}
	if (!stash || !*stash)
		return free_stash(stash);
	i = 0;
	while (stash[i] && stash[i] != 10)
		i++;
	line = malloc(i + 2);
	i = -1;
	while (stash[++i] && stash[i] != 10)
		line[i] = stash[i];
	if (stash[i] == 10)
		line[i++] = 10;
	line[i] = 0;
	tmp = stash[i] ? ft_strdup(stash + i) : 0;
	free(stash);
	stash = tmp;
	return line;
}

int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	int	i = 16;
	char	*line;
	if (fd == -1)
	{
		printf("error archivo\n");
		return 1;
	}
	while (i--)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line)
			free(line);
		else
			printf("\n");
	}
	close(fd);
	return 0;
}


