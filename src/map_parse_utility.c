/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:57:02 by cliew             #+#    #+#             */
/*   Updated: 2024/08/27 16:01:34 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char* trim_whitespace(char* str) {
    char* end;

    // Trim leading space by moving the str pointer to the first non-whitespace character
    while (ft_isspace((unsigned char)*str)) str++;

    if (*str == 0)  // All spaces, return an empty string
        return str;

    // Find the end of the string
    end = str + ft_strlen(str) - 1;

    // Move backwards from the end, skipping whitespace characters
    while (end > str && ft_isspace((unsigned char)*end)) {
        end--;
    }

    // Set the new null terminator character after the last non-whitespace character
    end[1] = '\0';

    return str;
}



int count_words_from_array(char **words) {
    int count = 0;
    while (words[count] != NULL) {
        count++;
    }
    return count;
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
int check_invalid_rgb(char* word)
{
	char ** words;
	int count;
	// int value;

	count=0;
	words=ft_split(word, ',');
    while (words[count] != NULL) {

		if  (!ft_isinteger(words[count]) || ft_atoi(words[count]) <0 || ft_atoi(words[count])>255)
		{
			printf("Error\nRGB value must be between 0 and 255\n");
			free_split_result(words);
			return 1;
		}

		count++;
    }
	if (count!=3)
	{
		printf("Error\nRGB value must be 3 values between 0 and 255,seprated by comma (e.g. 0,125,255)\n");
		free_split_result(words);

		return 1;
	}
	free_split_result(words);
	return 0;
}

int** initializeArray(int x, int y) {
		int i;
		int **cub_map_array;

		cub_map_array = (int **)malloc(x * sizeof(int *));
		if (cub_map_array == NULL) {
			// Handle memory allocation failure
			exit(1);
		}

		for (i = 0; i < x; i++) {
			cub_map_array[i] = (int *)calloc(y, sizeof(int));
			if (cub_map_array[i] == NULL) {
				// Handle memory allocation failure
				exit(1);
			}
		}

		return cub_map_array;
	}

