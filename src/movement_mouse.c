/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:56:04 by toto              #+#    #+#             */
/*   Updated: 2024/09/09 17:56:10 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void init_last_pos(int x, int y, int *last_x, int *last_y)
{
	if (*last_x == -1 || *last_y == -1)
	{
		*last_x = x;
		*last_y = y;
	}
}

void calc_mouse_delta(int x, int y, int *last_x, int *last_y, int *dx, int *dy)
{
	*dx = x - *last_x;
	*dy = y - *last_y;
	*last_x = x;
	*last_y = y;
}

float calc_rotation_angle(int dx, float speed)
{
	return dx * speed;
}

// void rotate_vector(float *x, float *y, float angle)
// {
// 	float old_x = *x;
// 	*x = old_x * cos(angle) - *y * sin(angle);
// 	*y = old_x * sin(angle) + *y * cos(angle);
// }

void rotate_player(t_game *game, float angle)
{
	if (game->player->is_extracting == 0)
	{
		rotate_vector(&game->player->direction.x, &game->player->direction.y, angle);
		rotate_vector(&game->player->plane.x, &game->player->plane.y, angle);
	}

}

void adjust_pitch(t_game *game, int dy, float speed)
{
	float change = -dy * speed;
	if (game->player->is_extracting == 0)
	{
		if (fabs(change) > 0.001)
		{
			game->player->pitch += change;
			game->player->pitch = fmax(-1.0, fmin(1.0, game->player->pitch));
		}
	}

}

int handle_mouse_move(int x, int y, t_game *game)
{
	// static int last_x = -1;
	// static int last_y = -1;
	(void)x;
	(void)y;

	int dx, dy;
	float angle;
	float rot_speed = 0.005;  // Half of the original value
	float pitch_speed = 0.001;
	int center_x = DEFAULT_S_WIDTH / 2;
	int center_y = DEFAULT_S_HEIGHT / 2;

	// Get the current mouse position
	int current_x, current_y;
	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &current_x, &current_y);

	// Calculate the delta from the center
	dx = current_x - center_x;
	dy = current_y - center_y;

	// Only process if there's actual movement
	if (dx != 0 || dy != 0)
	{
		angle = calc_rotation_angle(dx, rot_speed);
		if (fabs(angle) > 0.001)
		{
			rotate_player(game, angle);
		}

		adjust_pitch(game, dy, pitch_speed);

		// Move the mouse back to the center
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center_x, center_y);
	}

	return (0);
}

void play_random_strike_sound(t_game *game)
{
	// Generate a random number between 0 and 2
	int random_strike = random_int(game, 3);

	// Create the audio file name based on the random number
	char audio_file[] = "audio/strike00.mp3";
	audio_file[13] = '0' + random_strike;

	// Play the selected audio file with no delay
	play_audio_file(game, audio_file, 0);
	play_audio_file(game, "audio/orbitalcall.mp3", 0);
}


int handle_mouse_click(int button, int x, int y, void *param)
{
	t_game *game = (t_game *)param;
	if (button == 1 && game->game_sequence == 3)
	{
		printf("Shooting at position (%d, %d)\n", x, y);

		game->is_shooting = 1;
		int random_value = random_int(game, 6);
		play_gun_sound(game);

		// If the random value is 0 (25% chance), print the special text
		if (random_value == 0)
		{
			printf("Get some get some\n");
			stop_audio_file(game, "audio/getsome.mp3");
			play_audio_file(game, "audio/getsome.mp3", 0);
			// play audio
		}
	}
	return (0);
}

int handle_mouse_release(int button, int x, int y, void *param)
{
	t_game *game = (t_game *)param;

	(void)y;
	(void)x;
	if (button == 1)
		game->is_shooting = 0;
	return (0);
}
