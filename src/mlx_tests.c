# include "cube3d.h"


int mlx_test_xpm_to_pixels(void)
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    int img_width, img_height;
    char *img_data;
    int bpp, size_line, endian;

    // Initialize MLX and create a new window
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Pixel by Pixel Texture Example");

    // Load an XPM file as an image
    img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/eagle.xpm", &img_width, &img_height);
    if (!img_ptr) {
        printf("Error loading XPM file\n");
        return 1;
    }

    // Get the image data from the image pointer
    img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

    // Store and manipulate pixels as needed
    int x, y;
    for (y = 0; y < img_height; y++) {
        for (x = 0; x < img_width; x++) {
            // Calculate the position in the image data array
            int pixel_pos = (x * (bpp / 8)) + (y * size_line);

            // Extract the color of each pixel (assuming the color is stored in 0xRRGGBB format)
            int color = *(int *)(img_data + pixel_pos);

            // Manipulate or store the color as needed, then put it on the window
            // For example, you can directly put the pixel on the window or store it for later use
            mlx_pixel_put(mlx_ptr, win_ptr, 50 + x, 50 + y, color);
        }
    }

    // Handle the loop for the window (necessary for image display)
    mlx_loop(mlx_ptr);

    return 0;
}

int mlx_test_xpm_to_pixels_scaled_to_screen(void)
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    int img_width, img_height;
    char *img_data;
    int bpp, size_line, endian;

    // Initialize MLX and create a new window
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Scaled Texture Example");

    // Load an XPM file as an image
    img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/eagle.xpm", &img_width, &img_height);
    if (!img_ptr) {
        printf("Error loading XPM file\n");
        return 1;
    }

    // Get the image data from the image pointer
    img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

    // Calculate scale factors
    double scaleX = 800.0 / img_width;
    double scaleY = 600.0 / img_height;

    // Render each pixel scaled
    int screenX, screenY, texX, texY;
    for (screenY = 0; screenY < 600; screenY++) {
        for (screenX = 0; screenX < 800; screenX++) {
            texX = (int)(screenX / scaleX);
            texY = (int)(screenY / scaleY);

            // Calculate the position in the image data array
            int pixel_pos = (texX * (bpp / 8)) + (texY * size_line);

            // Extract the color of each pixel (assuming the color is stored in 0xRRGGBB format)
            int color = *(int *)(img_data + pixel_pos);

            // Put the pixel on the window at the scaled position
            mlx_pixel_put(mlx_ptr, win_ptr, screenX, screenY, color);
        }
    }

    // Handle the loop for the window (necessary for image display)
    mlx_loop(mlx_ptr);

    return 0;
}

int mlx_test_xpm_to_pixels_scaled_w_animation(void)
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    int img_width, img_height;
    char *img_data;
    int bpp, size_line, endian;

    // Initialize MLX and create a new window
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Perspective Wall Rendering");

    // Load an XPM file as an image
    img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/eagle.xpm", &img_width, &img_height);
    if (!img_ptr) {
        printf("Error loading XPM file\n");
        return 1;
    }

    // Get the image data from the image pointer
    img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

    // Render each pixel with vertical perspective
    double initial_scaleY = 600.0 / img_height;
    for (int slice = 0; slice < 600; slice++) {
        double sliceHeight = 600 - slice;  // Decreasing height for each slice
        double perspectiveFactor = sliceHeight / 600.0;
        int drawStartY = (600 - sliceHeight) / 2;  // Centering the slice vertically
        int drawEndY = drawStartY + sliceHeight;

        for (int screenY = drawStartY; screenY < drawEndY; screenY++) {
            double relY = (screenY - drawStartY) / perspectiveFactor / initial_scaleY;
            int texY = (int)(relY) % img_height;  // Ensure it loops within texture bounds

            for (int screenX = 0; screenX < 800; screenX++) {
                int texX = (int)(screenX * img_width / 800.0) % img_width;  // Texture X coordinate

                // Calculate the position in the image data array
                int pixel_pos = (texX * (bpp / 8)) + (texY * size_line);

                // Extract the color of each pixel
                int color = *(int *)(img_data + pixel_pos);

                // Put the pixel on the window at the scaled position
                mlx_pixel_put(mlx_ptr, win_ptr, screenX, screenY, color);
            }
        }
    }

    // Handle the loop for the window (necessary for image display)
    mlx_loop(mlx_ptr);

    return 0;
}

int mlx_test_xpm_to_pixels_scaled_w_perspective(void) {
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    int img_width, img_height;
    char *img_data;
    int bpp, size_line, endian;

    // Initialize MLX and create a new window
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Two-Point Perspective");

    // Load an XPM file as an image
    img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/bluestone.xpm", &img_width, &img_height);
    if (!img_ptr) {
        printf("Error loading XPM file\n");
        return 1;
    }

    // Get the image data from the image pointer
    img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

    // Render each vertical line with two-point perspective
    for (int screenX = 0; screenX < 800; screenX++) {
        double ratio = (double)screenX / 800;
        int drawStart = 300 - (int)(300 * ratio); // Starts lower on the sides and higher in the center
        int drawEnd = 600 - drawStart; // Ends higher on the sides and lower in the center

        for (int screenY = drawStart; screenY < drawEnd; screenY++) {
            int texX = (int)(screenX * img_width / 800.0) % img_width;
            int texY = (int)((screenY - drawStart) * img_height / (drawEnd - drawStart)) % img_height;

            // Calculate the position in the image data array
            int pixel_pos = (texX * (bpp / 8)) + (texY * size_line);

            // Extract the color of each pixel
            int color = *(int *)(img_data + pixel_pos);

            // Put the pixel on the window at the scaled position
            mlx_pixel_put(mlx_ptr, win_ptr, screenX, screenY, color);
        }
    }

    // Handle the loop for the window (necessary for image display)
    mlx_loop(mlx_ptr);

    return 0;
}
