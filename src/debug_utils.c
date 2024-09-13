/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:19:19 by root              #+#    #+#             */
/*   Updated: 2024/07/09 18:19:19 by root             ###   ########.fr       */
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

void	print_movement_direction(t_game *game)
{
	if (game->player->direction.y < 0
		&& fabs(game->player->direction.y) > fabs(game->player->direction.x))
	{
		printf("You are moving north\n");
	}
}
