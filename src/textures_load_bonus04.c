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

void	validate_path_format(const char *path, int len, int min_len)
{
	if (len < min_len || ft_strcmp(path + len - 4, ".xpm") != 0)
	{
		printf("Error: Invalid path format\n");
	}
}

void	validate_digits(const char *path, int first, int second, int third)
{
	if (!ft_isdigit(path[first]) || !ft_isdigit(path[second]) ||
		(third != -1 && !ft_isdigit(path[third])))
	{
		printf("Error: Expected digits not found at correct positions\n");
	}
}

void	get_last_three_digit_indexes(const char *path, int *first, int *second, int *third)
{
	int	len;

	len = ft_strlen(path);
	validate_path_format(path, len, 7);
	*third = len - 5;
	*second = len - 6;
	*first = len - 7;
	validate_digits(path, *first, *second, *third);
}

void	get_last_two_digit_indexes(const char *path, int *first_digit, int *second_digit)
{
	int	len;

	len = ft_strlen(path);
	validate_path_format(path, len, 6);
	*second_digit = len - 5;
	*first_digit = len - 6;
	validate_digits(path, *first_digit, *second_digit, -1);
}

