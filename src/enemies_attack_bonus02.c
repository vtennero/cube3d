/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_attack_bonus02.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:03:42 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 14:30:31 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	apply_bump(t_game *game, float newX, float newY)
{
	if (!detect_collision(game, newX, newY))
	{
		game->player->position.x = newX;
		game->player->position.y = newY;
		return (1);
	}
	return (0);
}

void	apply_reduced_bump(t_game *game, float dx, \
float dy, float *bump_distance)
{
	float	new_x;
	float	new_y;
	float	min_bump;

	min_bump = 0.1f;
	while (*bump_distance > min_bump)
	{
		*bump_distance *= 0.5f;
		new_x = calculate_new_position_x(game, dx, *bump_distance);
		new_y = calculate_new_position_y(game, dy, *bump_distance);
		if (apply_bump(game, new_x, new_y))
			break ;
	}
}

void	bump_player(t_game *game, int enemy_index)
{
	float	dx;
	float	dy;
	float	bump_distance;
	float	new_x;
	float	new_y;

	bump_distance = 0.5f;
	calculate_vector(game, enemy_index, &dx, &dy);
	normalize_vector(&dx, &dy);
	new_x = calculate_new_position_x(game, dx, bump_distance);
	new_y = calculate_new_position_y(game, dy, bump_distance);
	if (!apply_bump(game, new_x, new_y))
		apply_reduced_bump(game, dx, dy, &bump_distance);
}
