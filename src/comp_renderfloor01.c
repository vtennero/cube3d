void render_floor(t_game *game)
{
    if (!game || !game->player || !game->map || !game->floor_texture_map)
    {
        fprintf(stderr, "Error: Invalid game state in render_floor\n");
        return;
    }

    // printf("Starting render_floor. Map dimensions: %d x %d\n", game->map->width, game->map->height);

    for (int y = DEFAULT_S_HEIGHT / 2; y < DEFAULT_S_HEIGHT; y++)
    {
        float rayDirX0 = game->player->direction.x - game->player->plane.x;
        float rayDirY0 = game->player->direction.y - game->player->plane.y;
        float rayDirX1 = game->player->direction.x + game->player->plane.x;
        float rayDirY1 = game->player->direction.y + game->player->plane.y;

        int p = y - DEFAULT_S_HEIGHT / 2;
        float posZ = 0.5 * DEFAULT_S_HEIGHT;
        float rowDistance = posZ / p;

        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / DEFAULT_S_WIDTH;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / DEFAULT_S_WIDTH;

        float floorX = game->player->position.x + rowDistance * rayDirX0;
        float floorY = game->player->position.y + rowDistance * rayDirY0;

        for (int x = 0; x < DEFAULT_S_WIDTH; ++x)
        {
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);

            if (cellX < 0 || cellX >= game->map->width || cellY < 0 || cellY >= game->map->height)
            {
                // printf("Out of bounds: cellX=%d, cellY=%d\n", cellX, cellY);
                floorX += floorStepX;
                floorY += floorStepY;
                continue;
            }

            int texture_index = game->floor_texture_map[cellY][cellX];

            if (texture_index < 0 || texture_index >= MAX_FLOOR_TEXTURES)
            {
                printf("Invalid texture index: %d at cellX=%d, cellY=%d\n", texture_index, cellX, cellY);
                floorX += floorStepX;
                floorY += floorStepY;
                continue;
            }

            t_texture *current_texture = &game->floortextures[texture_index];
            // printf("render floor: x= %d textureindex is %d\n", x, texture_index);
            if (!current_texture || !current_texture->data)
            {
                printf("Invalid texture at index: %d\n", texture_index);
                floorX += floorStepX;
                floorY += floorStepY;
                continue;
            }

            float fracX = floorX - cellX;
            float fracY = floorY - cellY;
            int tx = (int)(fracX * current_texture->width);
            int ty = (int)(fracY * current_texture->height);

            // if (tx < 0 || ty < 0 || tx >= current_texture->width || ty >= current_texture->height) {
            //     printf("Suspicious texture coordinates: tx=%d, ty=%d, texture size=%dx%d\n",
            //            tx, ty, current_texture->width, current_texture->height);
            //     printf("fracX=%f, fracY=%f, floorX=%f, floorY=%f\n", fracX, fracY, floorX, floorY);
            // }
            int color = get_floor_texture_color(current_texture, tx, ty);
            img_pix_put(&game->img, x, y, color);

            floorX += floorStepX;
            floorY += floorStepY;
        }
    }

    // printf("Finished render_floor\n");
}