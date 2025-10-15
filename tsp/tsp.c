/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 01:17:28 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/15 02:05:26 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <float.h>

float	(*cities)[2];
int		g_size;

// compute the distance between two points
float	distance(float a[2], float b[2])
{
	return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

float	get_total(int *path)
{
	int		cur, next, i;
	float	total = 0.0f;

	for (i = 0; i < g_size - 1; i++)
	{
		cur = path[i];
		next = path[i + 1];
		total += distance(cities[cur], cities[next]);
	}
	cur = path[i];
	next = path[0];
	total += distance(cities[cur], cities[next]);
	return total;
}

void	solve(int *path, int cur, float *best)
{
	if (cur == g_size)
	{
		float	total = get_total(path);
		if (total < *best)
			*best = total;
		return;
	}
	for (int i = cur; i < g_size; i++)
	{
		int	tmp = path[cur];
		path[cur] = path[i];
		path[i] = tmp;
		solve(path, cur + 1, best);
		tmp = path[cur];
		path[cur] = path[i];
		path[i] = tmp;
	}
}

float tsp(float (*array)[2], ssize_t size)
{
    float best_distance;
    // ... YOUR CODE HERE 

	best_distance = FLT_MAX;
	if (size <= 1)
		return 0.0f;
	int	*path = malloc(sizeof(int) * size);
	if (!path)
		return FLT_MAX;
	for (int i = 0; i < size; i++)
		path[i] = i;
	cities = array;
	g_size = size;
	solve(path, 1, &best_distance);
	free(path);

    return (best_distance);
}

ssize_t    file_size(FILE *file)
{
    char    *buffer = NULL;
    size_t    n = 0;
    ssize_t ret;

    errno = 0;

    for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

    free(buffer);
    if (errno || fseek(file, 0, SEEK_SET))
        return -1;
    return ret;
}

int        retrieve_file(float (*array)[2], FILE *file)
{
    int tmp;
    for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
        if (tmp != 2)
        {
            errno = EINVAL;
            return -1;
        }
    if (ferror(file))
        return -1;
    return 0;
}

int        main(int ac, char **av)
{
    char *filename = "stdin";
    FILE *file = stdin;
    if (ac > 1)
    {
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file)
    {
        fprintf(stderr, "Error opening %s: %m\n", filename);
        return 1;
    }

    ssize_t size = file_size(file);
    if (size == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    float (*array)[2] = calloc(size, sizeof (float [2]));
    if (!array)
    {
        fprintf(stderr, "Error: %m\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file) == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", av[1]);
        fclose(file);
        free(array);
        return 1;
    }
    if (ac > 1)
        fclose(file);

    printf("%.2f\n", tsp(array, size));
    free(array);
    return (0);
}