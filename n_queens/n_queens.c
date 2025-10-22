/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:07:19 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/23 01:14:43 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	n;
int	*board;

void	print_solution(void)
{
	for (int i = 0; i < n; i++)
	{
		fprintf(stdout, "%i", board[i]);
		if (i < n - 1)
			fprintf(stdout, " ");
	}
	fprintf(stdout, "\n");
}

int	ft_abs(int nbr)
{
	if (nbr < 0)
		return -nbr;
	return nbr;
}

int	is_safe(int row, int col)
{
	for (int i = 0; i < col; i++)
	{
		if (board[i] == row)
			return 0;
		if (ft_abs(board[i] - row) == ft_abs(i - col))
			return 0;
	}
	return 1;
}

void	solve(int col)
{
	if (col == n)
	{
		print_solution();
		return;
	}
	for (int row = 0; row < n; row++)
	{
		if (is_safe(row, col))
		{
			board[col] = row;
			solve(col + 1);
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	n = atoi(argv[1]);
	if (n < 4)
		return 0;
	board = malloc(sizeof(int) * n);
	if (!board)
		return 1;
	solve(0);
	free(board);
	return 0;
}
