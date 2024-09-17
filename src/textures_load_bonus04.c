/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures05_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:13:35 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:14:00 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	validate_path_format(const char *path, int len, int min_len)
{
	if (len < min_len || ft_strcmp(path + len - 4, ".xpm") != 0)
	{
		printf("Error: Invalid path format\n");
	}
	return (0);
}

int	validate_digits(const char *path, int first, int second, int third)
{
	if (!ft_isdigit(path[first]) || !ft_isdigit(path[second])
		|| (third != -1 && !ft_isdigit(path[third])))
	{
		printf("Error: Expected digits not found at correct positions\n");
	}
	return (0);
}

int	get_last_three_digit_indexes(char *path, int *f, int *s, int *t)
{
	int	len;

	len = ft_strlen(path);
	validate_path_format(path, len, 7);
	*t = len - 5;
	*s = len - 6;
	*f = len - 7;
	validate_digits(path, *f, *s, *t);
	return (0);
}

int	get_last_two_digit_indexes(char *path, int *f, int *s)
{
	int	len;

	len = ft_strlen(path);
	validate_path_format(path, len, 6);
	*s = len - 5;
	*f = len - 6;
	validate_digits(path, *f, *s, -1);
	return (0);
}
