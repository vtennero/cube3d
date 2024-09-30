/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus10.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:13:02 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/30 16:06:09 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	handle_enemy_hit(t_game *game, int enemy_index)
{
	game->enemies[enemy_index].is_alive = 0;
	add_script(game, play_bug_death, 0);
}

int	is_game_state_valid(t_game *game)
{
	if (!game || game->num_enemies <= 0 || !game->enemies)
	{
		printf("Error: Invalid game state in check_enemy_at_center\n");
		return (0);
	}
	return (1);
}

void	check_enemy_at_center(t_game *game)
{
	t_vector2d	center;
	int			i;

	if (!is_game_state_valid(game))
		return ;
	center = calculate_screen_center(game);
	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].is_alive)
		{
			if (process_enemy(game, i, center))
				return ;
		}
		i++;
	}
}

void	reinitialize_enemy(t_enemy *enemy, float x, float y)
{
	enemy->position.x = x + 0.5f;
	enemy->position.y = y + 0.5f;
	enemy->is_alive = 1;
	enemy->frame_count = 0;
	enemy->current_frame = 0;
	enemy->momentum = 0;
	enemy->animation_steps = 0;
}

int	randomize_dead_enemy_positions(t_game *game)
{
	int	i;
	int	x;
	int	y;
	int	enemies_repositioned;

	enemies_repositioned = 0;
	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].is_alive == 0)
		{
			x = random_int(game, game->map->width);
			y = random_int(game, game->map->height);
			while (game->map->data[y][x] == 1)
			{
				x = random_int(game, game->map->width);
				y = random_int(game, game->map->height);
			}
			reinitialize_enemy(&game->enemies[i], (float)x, (float)y);
			enemies_repositioned++;
		}
		i++;
	}
	return (enemies_repositioned);
}
