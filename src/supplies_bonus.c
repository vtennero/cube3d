/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supplies_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:21:46 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/10 11:21:46 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void render_supply_take(t_game *game)
{
	int x, y;
	int solid_white = 0xFFFFFF;

	if (game->player->taking_supplies)
	{
		for (y = 0; y < game->screen_height; y++)
	{
		for (x = 0; x < game->screen_width; x++)
		{
			if ((x + y) % 3 == 0)
			{
				img_pix_put(&game->img, x, y, solid_white);
			}
		}
	}
	}

}

int find_closest_supply(t_game *game)
{
	int closest_index = -1;
	float closest_distance_squared = SUPP_DIST * SUPP_DIST;

	for (int i = 0; i < game->num_supplies; i++)
	{
		if (!game->supplies[i].collected)
		{
			float dx = game->player->position.x - game->supplies[i].position.x;
			float dy = game->player->position.y - game->supplies[i].position.y;

			float distance_squared = dx * dx + dy * dy;

			if (distance_squared <= closest_distance_squared)
			{
				closest_distance_squared = distance_squared;
				closest_index = i;
			}
		}
	}

	return closest_index;
}


int find_supply_on_player_tile(t_game *game)
{
	for (int i = 0; i < game->num_supplies; i++)
	{
		if (!game->supplies[i].collected)
		{
			if (fabs(game->player->position.x - game->supplies[i].position.x) < SUPP_T_EPS &&
				fabs(game->player->position.y - game->supplies[i].position.y) < SUPP_T_EPS)
			{
				return i;
			}
		}
	}

	return -1;
}

void render_supply(t_game *game, t_vector2d position)
{
	t_texture *supply_texture = &game->supplies_texture[0];
	render_sprite_common(game, position, supply_texture);
}


void render_supplies(t_game *game)
{
	for (int i = 0; i < game->num_supplies; i++)
	{
		if (!game->supplies[i].collected)
			render_supply(game, game->supplies[i].position);
	}
}

