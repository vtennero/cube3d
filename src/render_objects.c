/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 23:00:39 by root              #+#    #+#             */
/*   Updated: 2024/08/23 08:54:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int is_sprite_in_front(float transformY, int stripe, int screen_width)
{
	return (transformY > 0 && stripe > 0 && stripe < screen_width);
}

t_ray_node  *find_ray_node(t_game *game, int stripe)
{
	t_ray_node *current = game->ray_list;
	while (current && current->ray.x != stripe)
		current = current->next;
	return current;
}
