/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus07.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:12:38 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:10:58 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_collectible(t_game *game, t_vector2d position)
{
	t_texture	*collectible_texture;

	collectible_texture = &game->coll_texture[0];
	render_sprite_common(game, position, collectible_texture);
}

void	render_collectibles(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_collectibles)
	{
		if (!game->collectibles[i].collected)
		{
			render_collectible(game, game->collectibles[i].position);
		}
		i++;
	}
}
