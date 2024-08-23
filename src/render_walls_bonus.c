/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:42:52 by root              #+#    #+#             */
/*   Updated: 2024/07/09 18:51:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// int	get_texture_color(t_texture *texture, int x, int y)
// {
// 	int	pixel_pos;
// 	int	color;

// 	// printf("Getting texture color at (X: %d, Y: %d)\n", x, y);
// 	pixel_pos = y * texture->tex_line_len + x * (texture->tex_bpp / 8);
// 	color = *(int *)(texture->data + pixel_pos);
// 	return (color);
// }

int get_texture_color(t_texture *texture, int x, int y)
{
    int pixel_pos;
    int color;

    // Ensure x and y are within bounds
    x = x % texture->width;
    y = y % texture->height;

    pixel_pos = y * texture->tex_line_len + x * (texture->tex_bpp / 8);
    color = *(int *)(texture->data + pixel_pos);
    return (color);
}


void render_ray(t_img *img, t_ray ray, t_texture *texture, t_game *game)
{
    int pitch_offset = (int)(game->player->pitch * game->screen_height);
    double step = 1.0 * texture->height / ray.lineHeight;
    double texPos = (ray.draw_start - pitch_offset - game->screen_height / 2
            + ray.lineHeight / 2) * step;
    
    for (int y = ray.draw_start; y < ray.draw_end; y++)
    {
        int texY = (int)texPos & (texture->height - 1);
        texPos += step;
        
        // Scale texX to match the texture width
        int texX = (int)((double)ray.texX * texture->width / 1024) & (texture->width - 1);
        
        int color = get_texture_color(texture, texX, texY);
        img_pix_put(img, ray.x, y, color);
    }
}

void	render_ray_list(t_game *game)
{
	int i = 0;
	game->ray_list = calculate_rays(game, game->ray_list);
	t_ray_node *current = game->ray_list;

	while (current != NULL)
	{
		t_texture *used_texture = &game->walltextures[current->ray.wall_face];
		render_ray(&game->img, current->ray, used_texture, game);
		// (void)used_texture;
		current = current->next;
		i++;
	}
}

