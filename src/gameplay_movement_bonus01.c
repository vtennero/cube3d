/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement_bonus01.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:07:58 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 15:07:58 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


float calculate_dynamic_buffer(t_player *player, float base_speed)
{
	// Calculate buffer based on the dot product of direction and plane vectors
	float dir_mag = sqrt(player->direction.x * player->direction.x + player->direction.y * player->direction.y);
	float plane_mag = sqrt(player->plane.x * player->plane.x + player->plane.y * player->plane.y);
	float dot_product = player->direction.x * player->plane.x + player->direction.y * player->plane.y;

	float cosine_angle = dot_product / (dir_mag * plane_mag);
	float dynamic_buffer = base_speed * (1 - fabs(cosine_angle)); // Reduce buffer as angle approaches 90 degrees
	// printf("dynamic buffer %f\n", dynamic_buffer);
	return dynamic_buffer;
}

// Rotate a vector by a given angle
void rotate_vector(float *x, float *y, float angle)
{
	float old_x = *x;
	float old_y = *y;
	*x = old_x * cos(angle) - old_y * sin(angle);
	*y = old_x * sin(angle) + old_y * cos(angle);
}

// New function to calculate rotation
void calculate_rotation(t_game *game, float angle)
{
	rotate_player(game, angle);

	printf("New direction.x = %f, New direction.y = %f\n", game->player->direction.x, game->player->direction.y);
	const char *direction = get_cardinal_direction(game->player->direction.x, game->player->direction.y);
	printf("Facing direction: %s\n", direction);

	print_movement_direction(game);
}




