/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement_bonus04.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:49:53 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/13 12:49:53 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	mouse_adjust_pitch(t_game *game, int dy)
{
	float	change;

	change = -dy * MOUSE_PITCH_SPEED;
	if (game->player->is_extracting == 0)
	{
		if (fabs(change) > 0.001)
		{
			game->player->pitch += change;
			game->player->pitch = fmax(-1.0, fmin(1.0, game->player->pitch));
		}
	}
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	t_vector2d		center;
	t_vector2d		current_pos;
	t_vector2d		delta;
	float			angle;

	(void)x;
	(void)y;
	center.x = DEFAULT_S_WIDTH / 2;
	center.y = DEFAULT_S_HEIGHT / 2;
	current_pos = get_mouse_position(game);
	delta = calculate_mouse_delta(current_pos, center);
	if (delta.x != 0 || delta.y != 0)
	{
		angle = mouse_calc_rotation_angle(delta.x);
		if (fabs(angle) > 0.001)
			mouse_rotate_player(game, angle);
		mouse_adjust_pitch(game, delta.y);
		center_mouse(game, center);
	}
	return (0);
}

int	handle_mouse_click(int button, int x, int y, void *param)
{
	t_game	*game;
	int		random_value;

	(void)x;
	(void)y;
	game = (t_game *)param;
	if (button == 1 && game->game_sequence == 3)
	{
		game->is_shooting = 1;
		random_value = random_int(game, 6);
		play_gun_sound(game);
		if (random_value == 0)
		{
			stop_audio_file(game, "audio/getsome.mp3");
			play_audio_file(game, "audio/getsome.mp3", 0);
		}
	}
	return (0);
}

int	handle_mouse_release(int button, int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	(void)y;
	(void)x;
	if (button == 1)
	{
		game->is_shooting = 0;
	}
	return (0);
}
