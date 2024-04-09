/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:55:31 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/09 18:50:44 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int main()
{
    t_game* g = malloc(sizeof(t_game)); // Dynamically allocate memory for game

    // Check for allocation failure
    if (!g) {
        // Handle allocation failure (e.g., print error and exit)
    }

    int screen_width = 800;
    int screen_height = 600;

    initialize_game(g, screen_width, screen_height, "Raycaster");
	calculate_rays(g, screen_width);

    // Game loop and other operations...

    // Cleanup before exiting
    // Example cleanup:
    // free(g->map->tiles); // You'll need a more thorough cleanup, freeing each row of tiles
    // free(g->map);
    // free(g);

    return 0;
}

