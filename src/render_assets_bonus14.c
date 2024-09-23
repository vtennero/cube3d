/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus14.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:17:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:17:07 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_sprite_in_front(float transformY, int stripe, int screen_width)
{
	return (transformY > 0 && stripe > 0 && stripe < screen_width);
}

t_ray_node	*find_ray_node(t_game *game, int stripe)
{
	t_ray_node	*current;

	current = game->ray_list;
	while (current && current->ray.x != stripe)
		current = current->next;
	return (current);
}
