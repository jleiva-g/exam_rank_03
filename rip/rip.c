/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 01:59:28 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/14 02:25:48 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	total;

int	min_to_rm(char *s)
{
	int	open = 0, close = 0;
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
	}
	return open + close;
}

void	solve(int cur, int rm, char *s)
{
	if (!s[cur])
	{
		if (rm == total && !min_to_rm(s))
			puts(s);
		return;
	}
	if (rm > total)
		return;
	if (s[cur] == '(' || s[cur] == ')')
	{
		char	tmp = s[cur];
		s[cur] = ' ';
		solve(cur + 1, rm + 1, s);
		s[cur] = tmp;
		solve(cur + 1, rm, s);
	}
	else
		solve(cur + 1, rm, s);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		puts("");
		return 1;
	}
	char	*s = argv[1];
	total = min_to_rm(s);
	if (!total)
	{
		puts(s);
		return 0;
	}
	solve(0, 0, s);
	return 0;
}