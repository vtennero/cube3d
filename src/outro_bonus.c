

#include "cube3d.h"

void render_outro(t_game *game)
{
    int frame_to_render = get_current_frame_outro(&game->opening_start_time);
    // printf("render outro frame to render %d\n", frame_to_render);
    t_texture *outro_texture = &game->outro_texture[frame_to_render];

    if (outro_texture->img == NULL)
    {
        printf("Error: outro texture not loaded\n");
        return;
    }

    // Render the frame
    for (int y = 0; y < game->screen_height; y++)
    {
        // printf("rendering frame\n");
        for (int x = 0; x < game->screen_width; x++)
        {
            int tex_x = x * outro_texture->width / game->screen_width;
            int tex_y = y * outro_texture->height / game->screen_height;
            int color = get_texture_color(outro_texture, tex_x, tex_y);
            img_pix_put(&game->img, x, y, color);
        }
    }

    // Update game state
    game->current_frame = frame_to_render;

    // Check if we've reached the last frame and close properly
    if (frame_to_render == MAX_OUTRO_TEXTURES - 1)
		return;
    // {
	// 	sleep(10);
	// 	cleanup(game);
    // }
}