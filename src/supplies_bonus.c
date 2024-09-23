/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supplies_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:21:46 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/10 11:21:46 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_supply_take(t_game *game)
{
	int	x;
	int	y;
	int	solid_white;

	solid_white = 0xFFFFFF;
	if (game->player->taking_supplies)
	{
		y = 0;
		while (y < game->screen_height)
		{
			x = 0;
			while (x < game->screen_width)
			{
				if ((x + y) % 3 == 0)
					img_pix_put(&game->img, x, y, solid_white);
				x++;
			}
			y++;
		}
	}
}

int	find_closest_supply(t_game *game)
{
	int		closest_index;
	float	closest_distance;
	int		i;
	float	distance;

	closest_index = -1;
	closest_distance = SUPP_DIST;
	i = 0;
	while (i < game->num_supplies)
	{
		if (!game->supplies[i].collected)
		{
			distance = calculate_distance(game->player->position, \
			game->supplies[i].position);
			if (distance <= closest_distance)
			{
				closest_distance = distance;
				closest_index = i;
			}
		}
		i++;
	}
	return (closest_index);
}

int	find_supply_on_player_tile(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_supplies)
	{
		if (!game->supplies[i].collected)
		{
			if (fabs(game->player->position.x \
			- game->supplies[i].position.x) < SUPP_T_EPS \
			&& fabs(game->player->position.y \
				- game->supplies[i].position.y) < SUPP_T_EPS)
				return (i);
		}
		i++;
	}
	return (-1);
}

void	render_supply(t_game *game, t_vector2d position)
{
	t_texture	*supply_texture;

	supply_texture = &game->supplies_texture[0];
	render_sprite_common(game, position, supply_texture);
}

void	render_supplies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_supplies)
	{
		if (!game->supplies[i].collected)
		{
			render_supply(game, game->supplies[i].position);
		}
		i++;
	}
}
