/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:55:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/05/07 12:04:37 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	create_game_struct(t_game **game)
{
	*game = calloc(1, sizeof(t_game));
	if (*game == NULL)
		return (-1);
	(*game)->screen_height = DEFAULT_S_HEIGHT;
	(*game)->screen_width = DEFAULT_S_WIDTH;
	(*game)->ray_list = NULL;
	(*game)->frame_counter = 0;
	return (0);
}

int	create_map(t_game *game)
{
	// Implement map creation and initialization
	create_static_map(game);
	return (0);
}

int	create_player(t_game *game)
{
	// Allocate memory for the player structure
	t_player *player = malloc(sizeof(t_player));
	if (player == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for the player.\n");
		exit(1); // or handle the error as appropriate
	}

	// Initialize player position
	player->position.x = 22;
	player->position.y = 12;

	// Initialize player direction (looking along the negative x-axis)
	player->direction.x = -1.0f;
	player->direction.y = 0.0f;

	// Initialize the camera plane for the raycasting (related to the FOV)
	player->plane.x = 0.0f;  // Adjust this value to change the FOV
	player->plane.y = 0.66f; // This setting assumes a 66 degrees FOV

	// Initialize pitch (not needed for basic raycasting,
		// useful for up/down look)
	player->height = 0.2;
	player->pitch = 0.0f;
	// player->pitch = 0;
	// Assign the player to the game structure
	game->player = player;
	return (0);
}