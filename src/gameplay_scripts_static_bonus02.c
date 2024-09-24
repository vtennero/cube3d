/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_static_bonus02.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:00:33 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:51:03 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	script_strike_player(t_game *game)
{
	t_vector2d	strike_pos;
	t_vector2d	player_pos;
	t_vector2d	delta;
	float		distance;

	if (game->strike[0].is_active)
	{
		strike_pos = game->strike[0].position;
		player_pos = game->player->position;
		delta.x = strike_pos.x - player_pos.x;
		delta.y = strike_pos.y - player_pos.y;
		distance = sqrt(delta.x * delta.x + delta.y * delta.y);
		if (distance <= 5.0f)
			game->player->hp = 0;
	}
}

void	script_napalm_player(t_game *game, int strike_no, float radius)
{
	t_vector2d	strike_pos;
	t_vector2d	player_pos;
	t_vector2d	delta;
	float		distance;

	if (game->strike[strike_no].is_active)
	{
		strike_pos = game->strike[strike_no].position;
		player_pos = game->player->position;
		delta.x = strike_pos.x - player_pos.x;
		delta.y = strike_pos.y - player_pos.y;
		distance = sqrt(delta.x * delta.x + delta.y * delta.y);
		if (distance <= radius)
		{
			if (game->player->is_burning == 0)
				play_random_burn_cry(game);
			game->player->is_burning = 1;
		}
	}
}

void	script_barrage_player(t_game *game)
{
	t_vector2d	strike_pos;
	t_vector2d	player_pos;
	t_vector2d	delta;
	float		distance;

	if (game->strike[2].is_active)
	{
		strike_pos = game->strike[2].position;
		player_pos = game->player->position;
		delta.x = strike_pos.x - player_pos.x;
		delta.y = strike_pos.y - player_pos.y;
		distance = sqrt(delta.x * delta.x + delta.y * delta.y);
		if (distance <= 6.0f && game->strike[2].is_animating)
			game->player->hp = 0;
	}
}

void	player_burning(t_game *game)
{
	int	random_call;

	random_call = random_int(game, 5);
	if (game->player->is_burning == 1 && random_call == 0)
	{
		printf("🔥 Helldiver is burning!!! health %d\n", game->player->hp);
		game->player->is_hit = 1;
		add_script(game, get_hit, 1);
	}
}
