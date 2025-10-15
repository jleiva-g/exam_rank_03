/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:18:56 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/15 10:55:14 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	len = 0;
	while (s[len])
		len++;
	return len;
}

int	ft_factorial(int size)
{
	if (size <= 1)
		return 1;
	return (size * ft_factorial(size - 1));
}

void	ft_strcpy(char *dst, char *s)
{
	int	i;
	for (i = 0; s[i]; i++)
		dst[i] = s[i];
	dst[i] = '\0';
}

void	solve(int cur, int size, char *s, char ** all, int *index)
{
	if (cur == size)
	{
		ft_strcpy(all[(*index)], s);
		(*index)++;
		return;
	}
	for (int i = cur; i < size; i++)
	{
		char tmp = s[i];
		s[i] = s[cur];
		s[cur] = tmp;
		solve(cur + 1, size, s, all, index);
		tmp = s[i];
		s[i] = s[cur];
		s[cur] = tmp;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	for (int i = 0; s1[i] || s2[i]; i++)
		if (s1[i] != s2[i])
			return s1[i] - s2[i];
	return 0;
}

void	sort_res(char **all, int total)
{
	int i, j;
	for (i = 0; i < total; i++)
	{
		for (j = i + 1; j < total; j++)
		{
			if (ft_strcmp(all[i], all[j]) > 0)
			{
				char	*tmp = all[i];
				all[i] = all[j];
				all[j] = tmp;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		puts("");
		return 1;
	}
	char	*s = argv[1];
	int		size = ft_strlen(s);
	if (!size)
	{
		puts("");
		return 1;
	}
	int		total = ft_factorial(size);
	char	**all = malloc(sizeof(char *) * total);
	for (int i = 0; i < total; i++)
		all[i] = calloc(size + 1, sizeof(char));
	int	index = 0;
	solve(0, size, s, all, &index);
	sort_res(all, total);
	for (int i = 0; i < total; i++)
		puts(all[i]);
	return 0;
}
