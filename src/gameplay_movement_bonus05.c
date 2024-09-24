/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement_bonus05.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:41:17 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:42:57 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

float	mouse_calc_rotation_angle(int dx)
{
	return (dx * MOUSE_ROT_SPEED);
}

void	mouse_rotate_player(t_game *game, float angle)
{
	if (game->player->is_extracting == 0)
	{
		rotate_vector(&game->player->direction.x, \
		&game->player->direction.y, angle);
		rotate_vector(&game->player->plane.x, &game->player->plane.y, angle);
	}
}
