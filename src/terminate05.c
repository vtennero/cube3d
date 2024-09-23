/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate05.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:13:26 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 16:14:46 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	clean_player(t_game *game)
{
	free(game->player);
	game->player = NULL;
}

void	clean_mlx(t_game *game)
{
	if (game->img.mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

void	clean_rays(t_game *game)
{
	struct s_ray_node	*current;
	struct s_ray_node	*next;
	int					ray_count;

	ray_count = 0;
	if (game == NULL)
	{
		printf("Error: game pointer is NULL\n");
		return ;
	}
	current = game->ray_list;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
		ray_count++;
	}
	game->ray_list = NULL;
}
