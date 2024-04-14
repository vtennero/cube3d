/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_basic_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:01:37 by toto              #+#    #+#             */
/*   Updated: 2024/04/14 14:55:15 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// int mlx_basic_setup(void)
// {
// 	void    *mlx_ptr;
// 	void    *win_ptr;

// 	printf("mlx_basic_setup\n");
// 	mlx_ptr = mlx_init();
// 	if (!mlx_ptr)
// 		return (1);
// 	win_ptr = mlx_new_window (mlx_ptr, 300, 300, "Hello World");
// 	if (!win_ptr)
// 		return (2);
// 	mlx_loop(mlx_ptr);
// 	return (0);
// }

#include <mlx.h>
#include <stdlib.h>

// int mlx_basic_setup()
// {
//     void *mlx_ptr;
//     void *win_ptr;
//     int lineHeight = 100;  // Example height
//     int drawStart = 200;   // Start y-coordinate
//     int drawEnd = drawStart + lineHeight; // End y-coordinate
//     int x_position = 400;  // x-coordinate where the line will be drawn

//     mlx_ptr = mlx_init();
//     win_ptr = mlx_new_window(mlx_ptr, 800, 600, "MLX Window");

//     // Draw a vertical green line
//     for (int y = drawStart; y < drawEnd; y++)
//     {
//         mlx_pixel_put(mlx_ptr, win_ptr, x_position, y, 0x00FF00); // 0x00FF00 is the color code for green
//     }

//     mlx_loop(mlx_ptr);
//     return (0);
// }

int mlx_basic_setup()
{
    void *mlx_ptr;
    void *win_ptr;
    int num_lines = 5; // Number of lines to draw
    int spacing = 50;  // Spacing between each line

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "MLX Window");

    // Draw multiple vertical green lines
    for (int i = 0; i < num_lines; i++)
    {
        int x_position = 100 + i * spacing; // Calculate x position for each line
        for (int y = 100; y < 300; y++) // Example vertical range
        {
            mlx_pixel_put(mlx_ptr, win_ptr, x_position, y, 0x00FF00); // 0x00FF00 is the color code for green
        }
    }

    mlx_loop(mlx_ptr);
    return (0);
}