/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate04.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:09:41 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 16:14:33 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_texture_array(t_texture *texture_array, \
int num_items, t_game *game)
{
	int	i;

	if (!game || !texture_array)
		return ;
	i = 0;
	while (i < num_items)
	{
		destroy_texture(game, &texture_array[i]);
		i++;
	}
}

void	destroy_texture(t_game *game, t_texture *texture)
{
	if (texture->img)
	{
		mlx_destroy_image(game->mlx_ptr, texture->img);
		texture->img = NULL;
	}
}
