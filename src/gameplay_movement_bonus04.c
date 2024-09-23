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

void	init_last_pos(int x, int y, int *last_x, int *last_y)
{
	if (*last_x == -1 || *last_y == -1)
	{
		*last_x = x;
		*last_y = y;
	}
}

float	calc_rotation_angle(int dx)
{
	return (dx * MOUSE_ROT_SPEED);
}

void	rotate_player(t_game *game, float angle)
{
	if (game->player->is_extracting == 0)
	{
		rotate_vector(&game->player->direction.x, \
		&game->player->direction.y, angle);
		rotate_vector(&game->player->plane.x, &game->player->plane.y, angle);
	}
}

void	adjust_pitch(t_game *game, int dy)
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

t_vector2d	get_mouse_position(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &x, &y);
	return ((t_vector2d){x, y});
}

t_vector2d	calculate_mouse_delta(t_vector2d current_pos, t_vector2d center)
{
	return ((t_vector2d){current_pos.x - center.x, current_pos.y - center.y});
}

void	center_mouse(t_game *game, t_vector2d center)
{
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, (int)center.x, (int)center.y);
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
		angle = calc_rotation_angle(delta.x);
		if (fabs(angle) > 0.001)
			rotate_player(game, angle);
		adjust_pitch(game, delta.y);
		center_mouse(game, center);
	}
	return (0);
}

void	play_random_strike_sound(t_game *game)
{
	char	audio_file[18];
	int		random_strike;

	ft_strcpy(audio_file, "audio/strike00.mp3");
	random_strike = random_int(game, 3);
	audio_file[13] = '0' + random_strike;
	play_audio_file(game, audio_file, 0);
	play_audio_file(game, "audio/orbitalcall.mp3", 0);
}

int	handle_mouse_click(int button, int x, int y, void *param)
{
	t_game	*game;
	int		random_value;

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
