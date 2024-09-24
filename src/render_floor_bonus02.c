/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_bonus02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:57:46 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 17:00:22 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	calculate_floor_pixel_color(t_game *game, t_vector2d floor)
{
	t_vector2d	cell;
	t_vector2d	tex_coords;
	int			texture_index;
	t_texture	*current_texture;

	cell.x = (int)floor.x;
	cell.y = (int)floor.y;
	texture_index = get_floor_texture_index(game, cell.x, cell.y);
	current_texture = get_floor_texture(game, texture_index);
	if (current_texture && current_texture->data)
	{
		calc_texture_coords(current_texture, floor, &tex_coords);
		return (get_floor_texture_color(current_texture, \
		(int)tex_coords.x, (int)tex_coords.y));
	}
	return (0x707070);
}

int	get_floor_texture_color(t_texture *texture, int x, int y)
{
	int	index;

	if (!texture || !texture->data)
	{
		printf("Error: Invalid texture in get_floor_texture_color\n");
		return (0);
	}
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	index = y * texture->line_len + x * (texture->bpp / 8);
	if (index < 0 || index >= texture->line_len * texture->height)
	{
		printf("Error: Texture index out of bounds: %d\n", index);
		return (0);
	}
	return (*(int *)(texture->data + index));
}

void	calc_texture_coords(t_texture *texture, \
t_vector2d floor, t_vector2d *tex_coords)
{
	t_vector2d	frac;

	frac.x = floor.x - floorf(floor.x);
	frac.y = floor.y - floorf(floor.y);
	tex_coords->x = fmodf(frac.x * texture->width, texture->width);
	tex_coords->y = fmodf(frac.y * texture->height, texture->height);
	if (tex_coords->x < 0)
		tex_coords->x += texture->width;
	if (tex_coords->y < 0)
		tex_coords->y += texture->height;
}

int	get_floor_texture_index(t_game *game, int cell_x, int cell_y)
{
	if (cell_x >= 0 && cell_x < game->map->width \
	&& cell_y >= 0 && cell_y < game->map->height)
		return (game->floor_texture_map[cell_y][cell_x]);
	return (-1);
}

t_texture	*get_floor_texture(t_game *game, int texture_index)
{
	if (texture_index >= 0 && texture_index < T_N_FLOOR)
		return (&game->floortextures[texture_index]);
	return (NULL);
}
