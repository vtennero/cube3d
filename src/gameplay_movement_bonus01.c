/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement_bonus01.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:14:21 by cliew             #+#    #+#             */
/*   Updated: 2024/09/21 17:14:21 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

const char	*get_cardinal_direction(float x, float y)
{
	float	angle;
	float	pi_8;

	angle = atan2(y, x);
	if (angle < 0)
		angle += 2 * M_PI;
	pi_8 = M_PI / 8;
	if (angle < pi_8 || angle > 15 * pi_8)
		return ("East");
	else if (angle < 3 * pi_8)
		return ("North-East");
	else if (angle < 5 * pi_8)
		return ("North");
	else if (angle < 7 * pi_8)
		return ("North-West");
	else if (angle < 9 * pi_8)
		return ("West");
	else if (angle < 11 * pi_8)
		return ("South-West");
	else if (angle < 13 * pi_8)
		return ("South");
	return ("South-East");
}

float	calculate_dynamic_buffer(t_player *player, float base_speed)
{
	float	dir_mag;
	float	plane_mag;
	float	dot_product;
	float	cosine_angle;
	float	dynamic_buffer;

	dir_mag = sqrt(player->direction.x * player->direction.x
			+ player->direction.y * player->direction.y);
	plane_mag = sqrt(player->plane.x * player->plane.x + player->plane.y
			* player->plane.y);
	dot_product = player->direction.x * player->plane.x + player->direction.y
		* player->plane.y;
	cosine_angle = dot_product / (dir_mag * plane_mag);
	dynamic_buffer = base_speed * (1 - fabs(cosine_angle));
	return (dynamic_buffer);
}

void	rotate_vector(float *x, float *y, float angle)
{
	float	old_x;
	float	old_y;

	old_x = *x;
	old_y = *y;
	*x = old_x * cos(angle) - old_y * sin(angle);
	*y = old_x * sin(angle) + old_y * cos(angle);
}

void	calculate_rotation(t_game *game, float angle)
{
	const char	*direction;

	direction = NULL;
	mouse_rotate_player(game, angle);
	if (game->bonus == 0)
	{
		printf("New direction.x = %f, New direction.y = %f\n",
			game->player->direction.x, game->player->direction.y);
		direction = get_cardinal_direction(game->player->direction.x,
				game->player->direction.y);
		printf("Facing direction: %s\n", direction);
	}
}
