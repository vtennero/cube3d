void render_floor(t_game *game)
{
    if (!game || !game->player || !game->map || !game->floor_texture_map)
    {
        fprintf(stderr, "Error: Invalid game state in render_floor\n");
        return;
    }

    float pitch = game->player->pitch;
    int pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
    // int height_offset = (int)(game->player->height * DEFAULT_S_HEIGHT);
    int height_offset = 0;

    // Set horizon at the center of the screen
    int horizon = DEFAULT_S_HEIGHT / 2;

    // Calculate where to start drawing the floor
    int floor_start = horizon - pitch_pixel_offset + height_offset;
    if (floor_start < 0) floor_start = 0;
    if (floor_start >= DEFAULT_S_HEIGHT) floor_start = DEFAULT_S_HEIGHT - 1;

    for (int y = floor_start; y < DEFAULT_S_HEIGHT; y++)
    {
        float rayDirX0 = game->player->direction.x - game->player->plane.x;
        float rayDirY0 = game->player->direction.y - game->player->plane.y;
        float rayDirX1 = game->player->direction.x + game->player->plane.x;
        float rayDirY1 = game->player->direction.y + game->player->plane.y;

        // Adjust the calculation of p to account for pitch and height
        int p = y - (horizon - pitch_pixel_offset + height_offset);
        float posZ = 0.5 * DEFAULT_S_HEIGHT;

        // Calculate row distance
        float rowDistance = p > 0 ? posZ / p : 100000; // Avoid division by zero

        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / DEFAULT_S_WIDTH;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / DEFAULT_S_WIDTH;

        float floorX = game->player->position.x + rowDistance * rayDirX0;
        float floorY = game->player->position.y + rowDistance * rayDirY0;

        for (int x = 0; x < DEFAULT_S_WIDTH; ++x)
        {
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);

            if (cellX >= 0 && cellX < game->map->width && cellY >= 0 && cellY < game->map->height)
            {
                int texture_index = game->floor_texture_map[cellY][cellX];

                if (texture_index >= 0 && texture_index < MAX_FLOOR_TEXTURES)
                {
                    t_texture *current_texture = &game->floortextures[texture_index];

                    if (current_texture && current_texture->data)
                    {
                        float fracX = floorX - cellX;
                        float fracY = floorY - cellY;
                        int tx = (int)(fracX * current_texture->width) & (current_texture->width - 1);
                        int ty = (int)(fracY * current_texture->height) & (current_texture->height - 1);

                        int color = get_floor_texture_color(current_texture, tx, ty);
                        img_pix_put(&game->img, x, y, color);
                    }
                }
            }

            floorX += floorStepX;
            floorY += floorStepY;
        }
    }

    printf("Horizon: %d, Pitch offset: %d, Height offset: %d, Floor start: %d\n", horizon, pitch_pixel_offset, height_offset, floor_start);
}