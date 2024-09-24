/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus04.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:04:34 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 17:04:40 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	run_bonus_rendering(t_game *game)
{
	render_sky(game);
	render_floor(game);
	render_walls(game);
	render_collectibles(game);
	render_supplies(game);
	render_extract(game);
	render_enemies(game);
	render_eagle_strike(game);
	render_napalm(game);
	render_barrage(game);
	render_gun(game);
	render_health_bar(game);
	render_crosshair(game);
	render_hit(game);
	render_supply_take(game);
	render_respawn(game);
	render_pelican_inside(game);
}
