/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/04/09 17:55:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/05/07 12:04:37 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	initgame(t_game **game)
{
	create_map(*game);
	create_player(*game);
	if ((*game)->bonus)
	{
		ft_printf("*** HELLDIVERS 3D ***\n");
		create_collectibles(*game);
		create_extraction(*game);
		create_enemies(*game);
		create_supplies(*game);
		create_strike(*game);
		initialize_audio(*game);
	}
	else
		ft_printf("*** CUB3D ***\n");
	setup_game_mlx(*game);
	return (1);
}

int	create_game_struct(t_game **game, int is_bonus)
{
	*game = ft_calloc(1, sizeof(t_game));
	if (*game == NULL)
		return (-1);
	(*game)->loading = 0;
	(*game)->bonus = is_bonus;
	(*game)->screen_height = DEFAULT_S_HEIGHT;
	(*game)->screen_width = DEFAULT_S_WIDTH;
	(*game)->ray_list = NULL;
	(*game)->game_sequence = 0;
	(*game)->change_seq = 0;
	(*game)->current_frame = 0;
	(*game)->loop_count = 0;
	(*game)->is_shooting = 0;
	(*game)->current_shooting_frame = 0;
	(*game)->current_gun_frame = 0;
	(*game)->is_moving_fwd = 0;
	(*game)->script_manager = (t_script_manager){0};
	if (is_bonus)
		set_crosshair_position(*game);
	return (0);
}

int	create_map(t_game *game)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	ft_printf("initializing map\n");
	if (map == NULL)
	{
		ft_printf("Error\nMemory allocation failed for map structure.\n");
		exit(1);
	}
	ft_printf("Allocated memory for the map structure\n");
	map->width = ((game->cub_map_col_count + 1) / 2);
	map->height = game->cub_map_row_count;
	map->data = game->cub_map_array;
	game->map = map;
	ft_printf("initialized map\n");
	return (0);
}

void	set_player_direction(t_game *game, t_player *player)
{
	player->direction.x = 0.0f;
	player->direction.y = 0.0f;
	player->plane.x = 0.0f;
	player->plane.y = 0.0f;
	if (game->cub_player_o == 2)
	{
		player->direction.y = -1.0f;
		player->plane.x = 0.66f;
	}
	if (game->cub_player_o == 3)
	{
		player->direction.x = 1.0f;
		player->plane.y = 0.66f;
	}
	if (game->cub_player_o == 4)
	{
		player->direction.y = 1.0f;
		player->plane.x = -0.66f;
	}
	if (game->cub_player_o == 5)
	{
		player->direction.x = -1.0f;
		player->plane.y = -0.66f;
	}
}

int	create_player(t_game *game)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (player == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for the player.\n");
		exit(1);
	}
	player->position.x = (game->cub_player_y) + 0.5;
	player->position.y = (game->cub_player_x) + 0.5;
	set_player_direction(game, player);
	player->height = 0.0f;
	if (game->bonus == 1)
		player->height = 0.2f;
	player->pitch = 0.0f;
	player->hp = MAX_HEALTH;
	player->is_hit = 0;
	player->taking_supplies = 0;
	player->is_dead = 0;
	player->is_extracting = 0;
	player->is_burning = 0;
	game->player = player;
	return (0);
}
