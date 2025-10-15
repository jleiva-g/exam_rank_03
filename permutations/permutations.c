/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:18:56 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/15 11:10:26 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		size;
int		total;
char	**res;
int		r_index;

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

// void	solve(int cur, char *s, int *index)
void	solve(int cur, char *s)
{
	if (cur == size)
	{
		ft_strcpy(res[r_index], s);
		r_index++;
		return;
	}
	for (int i = cur; i < size; i++)
	{
		char tmp = s[i];
		s[i] = s[cur];
		s[cur] = tmp;
		solve(cur + 1, s);
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

void	sort_res(void)
{
	for (int i = 0; i < total; i++)
	{
		for (int j = i + 1; j < total; j++)
		{
			if (ft_strcmp(res[i], res[j]) > 0)
			{
				char	*tmp = res[i];
				res[i] = res[j];
				res[j] = tmp;
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
	size = ft_strlen(s);
	if (!size)
	{
		puts("");
		return 1;
	}
	total = ft_factorial(size);
	res = malloc(sizeof(char *) * total);
	for (int i = 0; i < total; i++)
		res[i] = malloc(sizeof(char) * (size + 1));
	solve(0, s);
	sort_res();
	for (int i = 0; i < total; i++)
		puts(res[i]);
	return 0;
}
