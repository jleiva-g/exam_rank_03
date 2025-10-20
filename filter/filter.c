/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:35:43 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/20 16:41:54 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_INPUT_BUFFER_SIZE (10000 + 1)

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i = 0;
	while (i < n && s1[i] == s2[i])
		i++;
	if (i == n)
		return 1;
	else
		return 0;
}

int	main(int argc, char **argv)
{
	if (argc != 2 || argv[1] == NULL || strlen(argv[1]) == 0)
		return 1;
	char *buffer = malloc(MAX_INPUT_BUFFER_SIZE);
	if (buffer == NULL)
	{
		perror("Error");
		return 1;
	}
	char	c;
	ssize_t	bread;
	int		i = 0;
	int		len = strlen(argv[1]);
	while ((bread = read(0, &c, 1)) > 0)
	{
		if (i > MAX_INPUT_BUFFER_SIZE - 1)
			break;
		buffer[i++] = c;
	}
	if (bread == -1)
	{
		perror("Error");
		free(buffer);
		return 1;
	}
	buffer[i] = '\0';
	int j = 0;
	while (buffer[j])
	{
		if (j + len <= i && ft_strncmp(&buffer[j], argv[1], len))
		{
			for (int k = 0; k < len; k++)
				write(1, "*", 1);
			j += len;
		}
		else
			write(1, &buffer[j++], 1);
	}
	free(buffer);
	return 0;
}
