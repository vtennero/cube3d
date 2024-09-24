/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_static_bonus01.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:00:25 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:48:24 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	play_bug_death(t_game *game)
{
	int		random_call;
	char	audio_file[16];

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
