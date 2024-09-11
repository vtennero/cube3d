/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: cliew <cliew@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/12 20:57:02 by cliew             #+#    #+#             */
/*   Updated: 2024/08/27 16:01:34 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*trim_whitespace(char *str)
{
	char	*end;

	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
	{
		end--;
	}
	end[1] = '\0';
	return (str);
}

int	count_words_from_array(char **words)
{
	int	count;

	count = 0;
	while (words[count] != NULL)
	{
		count++;
	}
	if (count==0)
		free_split_result(words);
	return (count);
}

int	ft_isinteger(char *number)
{
	int	i;

	i = 0;
	if (number[0] == '-')
		i = 1;
	if (number[0] == '0' && number[1] != '\0')
		return (0);
	if (number[0] == '-' && number[1] == '0')
		return (0);
	if (number[0] == '-' && number[1] == '\0')
		return (0);
	while (number[i] != '\0')
	{
		if (!ft_isdigit(number[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_invalid_rgb(char *word)
{
	char	**words;
	int		count;

	count = 0;
	words = ft_split(word, ',');
	while (words[count] != NULL)
	{
		if (!ft_isinteger(words[count]) || ft_atoi(words[count]) < 0
			|| ft_atoi(words[count]) > 255)
		{
			ft_printf("Error\nRGB value must be between 0 and 255\n");
			free_split_result(words);
			return (1);
		}
		count++;
	}
	if (count != 3)
	{
		ft_printf("Error\nRGB value must be 3 values between 0 and 255, "
			"separated by comma (e.g. 0,125,255)\n");
		free_split_result(words);
		return (1);
	}
	free_split_result(words);
	return (0);
}

int	**initialize_array(int x, int y)
{
	int	i;
	int	**cub_map_array;

	i = 0;
	cub_map_array = (int **)malloc(x * sizeof(int *));
	if (cub_map_array == NULL)
	{
		ft_printf("Error\nMemory allocation to cub_map_array Failed!");
		exit(1);
	}
	while (i < x)
	{
		cub_map_array[i] = (int *)ft_calloc(y, sizeof(int));
		if (cub_map_array[i] == NULL)
		{
			ft_printf("Error\nMemory allocation to cub_map_array[i] Failed!");
			exit(1);
		}
		i++;
	}
	return (cub_map_array);
}