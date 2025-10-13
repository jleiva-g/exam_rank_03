/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 04:18:47 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/13 04:37:50 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	n;
int	size;
int	*s;

void	print_res(int ssize, int *res)
{
	for (int i = 0; i < ssize; i++)
	{
		printf("%i", res[i]);
		if (i < ssize - 1)
			printf(" ");
	}
	printf("\n");
}

int	sub_sum(int ssize, int *res)
{
	int	sum = 0;
	for (int i = 0; i < ssize; i++)
		sum += res[i];
	return sum;
}

void	solve(int ssize, int cur, int *res)
{
	if (cur == size)
	{
		if (sub_sum(ssize, res) == n && ssize != 0)
			print_res(ssize, res);
		return;
	}
	solve(ssize, cur + 1, res);
	res[ssize] = s[cur];
	solve(ssize + 1, cur + 1, res);
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return 1;
	n = atoi(argv[1]);
	size = argc - 2;
	s = calloc(size, sizeof(int));
	if (!s)
		return 1;
	int	*res = calloc(size, sizeof(int));
	if (!res)
	{
		free(s);
		return 1;
	}
	for (int i = 0; i < size; i++)
		s[i] = atoi(argv[i + 2]);
	solve (0, 0, res);
	free(s);
	free(res);
	return 0;
}
