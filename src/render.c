/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:19:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/09 17:19:22 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// Initialize MiniLibX, window, and image buffer
void setup_mlx(t_game* game);

// Main rendering loop
void render_loop(t_game* game);

// Draw a single frame
void render_frame(t_game* game);

// Cleanup resources
void cleanup(t_game* game);