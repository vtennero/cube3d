/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strike02_bonus01.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:54:49 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:55:34 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_vector2d	generate_random_offset(t_game *game, float proximity_radius)
{
	float		angle;
	float		distance;
	t_vector2d	offset;

	angle = random_float(game) * 2 * M_PI;
	distance = random_float(game) * proximity_radius;
	offset.x = cosf(angle) * distance;
	offset.y = sinf(angle) * distance;
	return (offset);
}

t_vector2d	calc_barrage_new_pos(t_vector2d base_position, t_vector2d offset)
{
	t_vector2d	new_position;

	new_position.x = base_position.x + offset.x;
	new_position.y = base_position.y + offset.y;
	return (new_position);
}

t_vector2d	clamp_barr_pos(t_vector2d position, int map_width, int map_height)
{
	t_vector2d	clamped;

	clamped.x = fmax(0, fmin(position.x, map_width - 1));
	clamped.y = fmax(0, fmin(position.y, map_height - 1));
	return (clamped);
}

void	reset_strike_parameters(t_strike *strike)
{
	strike->frame_count = 0;
	strike->current_frame = 0;
	strike->is_active = 1;
	strike->is_launching = 1;
	strike->is_animating = 0;
	strike->delay_frames = 0;
	strike->delay_duration = 60 * 2;
}

void	randomize_barrage_location(t_game *game)
{
	float		proximity_radius;
	t_vector2d	offset;
	t_vector2d	new_position;
	int			attempts;

	proximity_radius = 10.0f;
	offset = generate_random_offset(game, proximity_radius);
	new_position = calc_barrage_new_pos(game->strike[2].base_position, offset);
	new_position = clamp_barr_pos(new_position, \
	game->map->width, game->map->height);
	attempts = 0;
	while (!is_valid_location(game, (int)new_position.x, \
	(int)new_position.y) && attempts < 10)
	{
		offset = generate_random_offset(game, proximity_radius);
		new_position = calc_barrage_new_pos(game->strike[2].base_position, \
		offset);
		new_position = clamp_barr_pos(new_position, game->map->width, \
		game->map->height);
		attempts++;
	}
	game->strike[2].position.x = new_position.x;
	game->strike[2].position.y = new_position.y;
	reset_strike_parameters(&game->strike[2]);
	print_barrage_loc(new_position, game->strike[2].base_position);
}
