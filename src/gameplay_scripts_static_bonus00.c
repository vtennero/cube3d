/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_static_bonus00.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:00:18 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/21 17:09:20 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	player_need_stims(t_game *game)
{
	int	random_value;

	random_value = random_int(game, 3);
	if (random_value == 0 && game->player->hp <= 0.25 * MAX_HEALTH)
	{
		stop_audio_file(game, "audio/stims00.mp3");
		play_audio_file(game, "audio/stims00.mp3", 0);
	}
}

void	script_skip_enter(t_game *game)
{
	if (game->change_seq == 1 && game->game_sequence < 3)
	{
		game->game_sequence++;
		game->change_seq = 0;
	}
}

void	play_bug_death(t_game *game)
{
	int		random_call;
	char	audio_file[15];

	random_call = random_int(game, 6);
	ft_strcpy(audio_file, "audio/bug00.mp3");
	audio_file[9] = '0' + random_call / 10;
	audio_file[10] = '0' + random_call % 10;
	stop_audio_file(game, audio_file);
	play_audio_file(game, audio_file, 0);
}

void	script_strike_enemies(t_game *game, int strike_no, float radius)
{
	t_vector2d	strike_pos;
	int			i;

	if (game->strike[strike_no].is_active)
	{
		strike_pos = game->strike[strike_no].position;
		i = 0;
		while (i < game->num_enemies)
		{
			check_and_kill_enemy(game, i, strike_pos, radius);
			i++;
		}
	}
}

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

float	calculate_distance(t_vector2d point1, t_vector2d point2)
{
	t_vector2d	delta;

	delta.x = point1.x - point2.x;
	delta.y = point1.y - point2.y;
	return (sqrt(delta.x * delta.x + delta.y * delta.y));
}

void	check_and_kill_enemy(t_game *game, int enemy_index, \
t_vector2d strike_pos, float radius)
{
	t_vector2d	enemy_pos;
	float		distance;

	if (game->enemies[enemy_index].is_alive)
	{
		enemy_pos = game->enemies[enemy_index].position;
		distance = calculate_distance(strike_pos, enemy_pos);
		if (distance <= radius)
		{
			game->enemies[enemy_index].is_alive = 0;
			add_script(game, play_bug_death, 0);
		}
	}
}

void	script_napalm_enemies(t_game *game, int strike_no, float radius)
{
	t_vector2d	strike_pos;
	int			i;

	if (game->strike[strike_no].is_active)
	{
		strike_pos = game->strike[strike_no].position;
		i = 0;
		while (i < game->num_enemies)
		{
			check_and_kill_enemy(game, i, strike_pos, radius);
			i++;
		}
	}
}

void	play_random_burn_cry(t_game *game)
{
	int		random_call;
	char	audio_file[16];

	random_call = random_int(game, 4);
	ft_strcpy(audio_file, "audio/burn00.mp3");
	audio_file[10] = '0' + random_call / 10;
	audio_file[11] = '0' + random_call % 10;
	play_audio_file(game, audio_file, 0);
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

void	script_barrage_enemies(t_game *game)
{
	t_vector2d	strike_pos;
	t_vector2d	enemy_pos;
	float		distance;
	int			i;

	if (game->strike[2].is_active)
	{
		strike_pos = game->strike[2].position;
		i = 0;
		while (i < game->num_enemies)
		{
			if (game->enemies[i].is_alive)
			{
				enemy_pos = game->enemies[i].position;
				distance = calculate_distance(strike_pos, enemy_pos);
				if (distance <= 6.0f && game->strike[2].is_animating)
				{
					game->enemies[i].is_alive = 0;
					add_script(game, play_bug_death, 0);
				}
			}
			i++;
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

void	play_land_voice(t_game *game)
{
	int		random_call;
	char	audio_file[16];

	random_call = random_int(game, 9);
	ft_strcpy(audio_file, "audio/land00.mp3");
	audio_file[10] = '0' + random_call / 10;
	audio_file[11] = '0' + random_call % 10;
	play_audio_file(game, audio_file, 0);
}

void	script_found_sth(t_game *game)
{
	if (game->game_sequence == 3
		&& game->collectibles->found == 0
		&& is_player_close_to_collectible(game) == 1)
	{
		play_audio_file(game, "audio/foundsth.mp3", 0);
		game->collectibles->found = 1;
	}
}

void	script_found_supplies(t_game *game)
{
	int	found;

	found = find_closest_supply(game);
	if (game->game_sequence == 3 && found >= 0 && \
	game->supplies[found].found == 0)
	{
		play_audio_file(game, "audio/supplies00.mp3", 0);
		game->supplies[found].found = 1;
	}
}

void	script_take_supplies(t_game *game)
{
	int	found;

	found = find_supply_on_player_tile(game);
	if (game->game_sequence == 3 && found >= 0 && \
	game->supplies[found].collected == 0)
	{
		printf("restored health\n");
		play_audio_file(game, "audio/stims02.mp3", 0);
		play_audio_file(game, "audio/stims03.mp3", 0);
		add_script(game, trigger_supply_take, 0);
		add_script(game, cancel_supply_take, 1);
		game->supplies[found].collected = 1;
		game->player->is_burning = 0;
		game->player->hp = MAX_HEALTH;
		stop_audio_file(game, "audio/burn00.mp3");
		stop_audio_file(game, "audio/burn01.mp3");
		stop_audio_file(game, "audio/burn02.mp3");
		stop_audio_file(game, "audio/burn03.mp3");
	}
}

void	script_die(t_game *game)
{
	if (game->player->hp <= 0 && game->player->is_dead == 0)
	{
		reset_game_start_time(game);
		game->player->is_dead = 1;
		game->player->is_burning = 0;
		game->player->hp = MAX_HEALTH;
		stop_audio_file(game, "audio/burn00.mp3");
		stop_audio_file(game, "audio/burn01.mp3");
		stop_audio_file(game, "audio/burn02.mp3");
		stop_audio_file(game, "audio/burn03.mp3");
		play_audio_file(game, "audio/death.mp3", 0);
		play_audio_file(game, "audio/kia00.mp3", 0);
	}
}

void	script_board(t_game *game)
{
	if (is_player_close_to_extract(game) && game->extract[0].is_landing == 1)
	{
		stop_audio_file(game, "audio/extractmusic00.mp3");
		play_audio_file(game, "audio/extractmusic01.mp3", 0);
		play_audio_file(game, "audio/extract04.mp3", 0);
		add_script(game, trigger_extract_victory, 5);
		game->extract[0].is_landing = 0;
		game->player->is_extracting = 1;
	}
}

void	script_takeoff(t_game *game)
{
	if (game->player->is_extracting == 1)
	{
		if (game->player->height >= 3)
		{
			game->player->is_extracting = 0;
			game->game_sequence = 4;
			reset_game_start_time(game);
		}
		else
		{
			game->player->height *= 1.03;
			game->player->is_extracting = 1;
		}
	}
}
