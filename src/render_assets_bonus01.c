/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus01.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:07:15 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:11:40 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_normal_gun_frame(t_game *game)
{
	int	frames_per_switch;

	frames_per_switch = 4;
	if (game->normal_gun_frame_counter >= frames_per_switch)
	{
		game->current_gun_frame = (game->current_gun_frame \
		+ 1) % game->num_gun_frames;
		game->normal_gun_frame_counter = 0;
	}
	game->normal_gun_frame_counter++;
}

void	update_shooting_gun_frame(t_game *game)
{
	int	frames_per_switch;
	int	num_shooting_frames;

	frames_per_switch = 4;
	num_shooting_frames = 4;
	if (game->shooting_gun_frame_counter >= frames_per_switch)
	{
		game->current_shooting_frame \
		= (game->current_shooting_frame + 1) % num_shooting_frames;
		game->shooting_gun_frame_counter = 0;
	}
	game->shooting_gun_frame_counter++;
}

t_texture	*select_gun_texture(t_game *game)
{
	if (game->is_shooting)
		return (&game->t_shoot[game->current_shooting_frame]);
	else
		return (&game->gun_textures[game->current_gun_frame]);
}
