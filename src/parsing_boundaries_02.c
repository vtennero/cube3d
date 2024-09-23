/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_boundaries_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/08 22:32:38 by cliew             #+#    #+#             */
/*   Updated: 2024/09/08 22:32:38 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	check_order_in_row(int **array, int row, int col_count, int direction)
{
	int	found_one;
	int	j;

	found_one = 0;
	if (direction == 1)
		j = 0;
	else
		j = col_count - 1;
	while ((direction == 1 && j < col_count) || (direction == -1 && j >= 0))
	{
		if (array[row][j] == 1)
			found_one = 1;
		else if (array[row][j] == 0 && !found_one)
		{
			ft_printf("Error\nRow %d Col %d is not valid.\n", row, j);
			return (0);
		}
		j += direction;
	}
	return (1);
}

int	check_order_in_column(int **array, int col, int row_count, int direction)
{
	int	found_one;
	int	i;

	found_one = 0;
	if (direction == 1)
		i = 0;
	else
		i = row_count - 1;
	while ((direction == 1 && i < row_count) || (direction == -1 && i >= 0))
	{
		if (array[i][col] == 1)
			found_one = 1;
		else if (array[i][col] == 0 && !found_one)
		{
			ft_printf("Error\nCol %d Row %d is not valid.\n", col, i);
			return (0);
		}
		i += direction;
	}
	return (1);
}

int	validate_map(int *valid, int **array, int row_count, int col_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < row_count)
	{
		if (!check_order_in_row(array, i, col_count, 1)
			|| !check_order_in_row(array, i, col_count, -1))
			*valid = 0;
		i++;
	}
	while (j < col_count)
	{
		if (!check_order_in_column(array, j, row_count, 1)
			|| !check_order_in_column(array, j, row_count, -1))
			*valid = 0;
		j++;
	}
	if (*valid)
		ft_printf("All rows and columns are valid.\n");
	return (*valid);
}
