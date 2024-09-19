/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/07/12 21:01:14 by cliew             #+#    #+#             */
/*   Updated: 2024/08/26 20:19:01 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	read_cub_texture_and_analyze_map(t_game *game)
{
	char	*line;
	int		map_start;

	map_start = 0;
	game->cub_fd = open(game->cub_filepath, O_RDONLY);
	if (game->cub_fd < 0)
		return (handle_error("Error\nCould not open file\n", -1));
	line = get_next_line(game->cub_fd);
	while (line != NULL)
	{
		game->cub_line_count++;
		if (check_line(game, line, &map_start) == -1)
			return (free_and_return(line, -1));
		if (map_start == 1)
		{
			if ((int)(ft_strlen(line)) > game->cub_map_col_count)
				game->cub_map_col_count = ft_strlen(line);
			game->cub_map_row_count++;
		}
		free(line);
		line = get_next_line(game->cub_fd);
	}
	close(game->cub_fd);
	return (1);
}

int	assign_texture(char **words, char **path, char *texture)
{
	if ((words[1]) && (ft_strlen(words[1]) > 0) && (words[1][ft_strlen(words[1])
			- 1] == '\n'))
		words[1][ft_strlen(words[1]) - 1] = '\0';
	if (words[0] && ft_strcmp(words[0], texture) == 0)
	{
		if (*path)
		{
			ft_printf("Error\n %s already set!\n", texture);
			return (-1);
		}
		else
			*path = ft_strdup(words[1]);
	}
	return (1);
}

int	assign_textures(t_game *game, char **words)
{
	if (assign_texture(words, &(game->walltextures[0].path), "NO") == -1)
		return (-1);
	if (assign_texture(words, &(game->walltextures[1].path), "EA") == -1)
		return (-1);
	if (assign_texture(words, &(game->walltextures[2].path), "SO") == -1)
		return (-1);
	if (assign_texture(words, &(game->walltextures[3].path), "WE") == -1)
		return (-1);
	if (assign_texture(words, &(game->floor_rgb[0].path), "F") == -1)
		return (-1);
	if (assign_texture(words, &(game->sky_rgb[0].path), "C") == -1)
		return (-1);
	return (1);
}

int	check_line(t_game *game, char *line, int *map_start)
{
	char	**words;
	int		word_count;

	line = trim_whitespace(line);
	words = ft_split(line, ' ');
	word_count = count_words_from_array(words);
	if (word_count == 0)
		return (0);
	if (((ft_strcmp(words[0], "0") == 0) || (ft_strcmp(words[0], "1") == 0))
		&& ((ft_strcmp(words[1], "0") == 0) || (ft_strcmp(words[1], "1") == 0))
		&& all_paths_set(game) == 1 && *map_start == 0)
	{
		*map_start = 1;
		return (freesplit_and_return(words, 1));
	}
	if (check_map_error(map_start, word_count, words) == -1)
		return (freesplit_and_return(words, -1));
	if (assign_textures(game, words) == -1)
		return (freesplit_and_return(words, -1));
	return (freesplit_and_return(words, 0));
}
