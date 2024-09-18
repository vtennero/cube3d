/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:44:50 by toto              #+#    #+#             */
/*   Updated: 2024/08/22 23:09:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// void render_collectible(t_game *game, t_vector2d position)
//
//
// {
//     t_texture *collectible_texture = &game->coll_texture[0];
//     render_sprite_common(game, position, collectible_texture);
// }


// void render_collectibles(t_game *game)
//
//
// {
//     for (int i = 0; i < game->num_collectibles; i++)
//
//
// {
//         if (!game->collectibles[i].collected)
//             render_collectible(game, game->collectibles[i].position);
//     }
// }



// Helper functions
// Helper functions
void col_initialize_sprite_render_context(t_sprite_render_context *ctx, t_game *game, t_vector2d position, t_texture *texture)
{
    ctx->game = game;
    ctx->position = position;
    ctx->texture = texture;
}

void col_calculate_sprite_position(t_sprite_render_context *ctx)
{
    ctx->calc.sprite_x = ctx->position.x - ctx->game->player->position.x;
    ctx->calc.sprite_y = ctx->position.y - ctx->game->player->position.y;
}

void col_transform_sprite(t_sprite_render_context *ctx)
{
    float invDet = 1.0f / (ctx->game->player->plane.x * ctx->game->player->direction.y - ctx->game->player->direction.x * ctx->game->player->plane.y);
    ctx->calc.transform_x = invDet * (ctx->game->player->direction.y * ctx->calc.sprite_x - ctx->game->player->direction.x * ctx->calc.sprite_y);
    ctx->calc.transform_y = invDet * (-ctx->game->player->plane.y * ctx->calc.sprite_x + ctx->game->player->plane.x * ctx->calc.sprite_y);
    ctx->calc.transform_y -= ctx->game->player->height;
}

void col_calculate_sprite_screen_x(t_sprite_render_context *ctx)
{
    ctx->calc.sprite_screen_x = (int)((ctx->game->screen_width / 2) * (1 + ctx->calc.transform_x / ctx->calc.transform_y));
}

void col_calculate_sprite_height(t_sprite_render_context *ctx)
{
    ctx->calc.sprite_height = abs((int)(ctx->game->screen_height / ctx->calc.transform_y)) * OBJECT_SIZE;
    int pitch_offset = (int)(ctx->game->player->pitch * ctx->game->screen_height);
    int height_offset = (int)(ctx->game->player->height * ctx->game->screen_height / ctx->calc.transform_y);

    ctx->calc.draw_start_y = -ctx->calc.sprite_height / 2 + ctx->game->screen_height / 2 + pitch_offset + height_offset;
    ctx->calc.draw_start_y = (ctx->calc.draw_start_y < 0) ? 0 : ctx->calc.draw_start_y;
    ctx->calc.draw_end_y = ctx->calc.sprite_height / 2 + ctx->game->screen_height / 2 + pitch_offset + height_offset;
    ctx->calc.draw_end_y = (ctx->calc.draw_end_y >= ctx->game->screen_height) ? ctx->game->screen_height - 1 : ctx->calc.draw_end_y;
}

void col_calculate_sprite_width(t_sprite_render_context *ctx)
{
    ctx->calc.sprite_width = abs((int)(ctx->game->screen_height / ctx->calc.transform_y)) * OBJECT_SIZE;
    ctx->calc.draw_start_x = -ctx->calc.sprite_width / 2 + ctx->calc.sprite_screen_x;
    ctx->calc.draw_start_x = (ctx->calc.draw_start_x < 0) ? 0 : ctx->calc.draw_start_x;
    ctx->calc.draw_end_x = ctx->calc.sprite_width / 2 + ctx->calc.sprite_screen_x;
    ctx->calc.draw_end_x = (ctx->calc.draw_end_x >= ctx->game->screen_width) ? ctx->game->screen_width - 1 : ctx->calc.draw_end_x;
}

// Main rendering functions
void col_calculate_sprite_transforms(t_sprite_render_context *ctx)
{
    col_calculate_sprite_position(ctx);
    col_transform_sprite(ctx);
}

void col_calculate_sprite_dimensions(t_sprite_render_context *ctx)
{
    col_calculate_sprite_screen_x(ctx);
    col_calculate_sprite_height(ctx);
    col_calculate_sprite_width(ctx);
}

void col_draw_sprite_stripe(t_sprite_render_context *ctx, int stripe)
{
    int tex_x = (int)(256 * (stripe - (-ctx->calc.sprite_width / 2 + ctx->calc.sprite_screen_x)) * ctx->texture->width / ctx->calc.sprite_width) / 256;

    t_ray_node *current = find_ray_node(ctx->game, stripe);

    if (current && ctx->calc.transform_y < current->ray.perpWallDist)
    {
        for (int y = ctx->calc.draw_start_y; y < ctx->calc.draw_end_y; y++)
        {
            int pitch_offset = (int)(ctx->game->player->pitch * ctx->game->screen_height);
            int height_offset = (int)(ctx->game->player->height * ctx->game->screen_height / ctx->calc.transform_y);
            int d = (y - pitch_offset - height_offset) * 256 - ctx->game->screen_height * 128 + ctx->calc.sprite_height * 128;
            int tex_y = ((d * ctx->texture->height) / ctx->calc.sprite_height) / 256;

            tex_y = (tex_y < 0) ? 0 : (tex_y >= ctx->texture->height) ? ctx->texture->height - 1 : tex_y;

            int color = get_pixel_color(tex_x, tex_y, ctx->texture->width, ctx->texture->height, ctx->texture->data, ctx->texture->tex_bpp, ctx->texture->tex_line_len);

            if (color != -1)
                img_pix_put(&ctx->game->img, stripe, y, color);
        }
    }
}

void col_render_sprite(t_sprite_render_context *ctx)
{
    for (int stripe = ctx->calc.draw_start_x; stripe < ctx->calc.draw_end_x; stripe++)
    {
        if (is_sprite_in_front(ctx->calc.transform_y, stripe, ctx->game->screen_width))
        {
            col_draw_sprite_stripe(ctx, stripe);
        }
    }
}

// Main entry point for sprite rendering
void col_render_sprite_common(t_game *game, t_vector2d position, t_texture *texture)
{
    t_sprite_render_context ctx;
    col_initialize_sprite_render_context(&ctx, game, position, texture);

    col_calculate_sprite_transforms(&ctx);
    col_calculate_sprite_dimensions(&ctx);
    col_render_sprite(&ctx);
}


// Existing functions updated to use the new structure
void render_collectible(t_game *game, t_vector2d position)
{
    t_texture *collectible_texture = &game->coll_texture[0];
    col_render_sprite_common(game, position, collectible_texture);
}

void render_collectibles(t_game *game)
{
    for (int i = 0; i < game->num_collectibles; i++)

   {
        if (!game->collectibles[i].collected)
            render_collectible(game, game->collectibles[i].position);
    }
}
