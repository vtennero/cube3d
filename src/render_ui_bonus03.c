/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui_bonus03.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:25:49 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:26:26 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_health_bar(t_game *game)
{
	t_health_bar	bar;

	calculate_health_bar_dimensions(game, &bar);
	draw_health_bar_border(game, &bar);
	draw_health_bar_fill(game, &bar);
}
