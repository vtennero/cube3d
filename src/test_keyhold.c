#include "cube3d.h"

#include <stdio.h>

int handle_keypress_test(int keysym, void *param)
{
    (void)param; // Unused parameter
    printf("Keypress: %d\n", keysym);
    return 0;
}

int handle_keyrelease_test(int keysym, void *param)
{
    (void)param; // Unused parameter
    printf("Keyrelease: %d\n", keysym);
    return 0;
}

int test_keyhold(void)
{
    void *mlx_ptr;
    void *win_ptr;

    // Initialize the MiniLibX graphics library
    mlx_ptr = mlx_init();
    if (mlx_ptr == NULL)
    {
        fprintf(stderr, "Error: Failed to initialize MiniLibX.\n");
        return 1;
    }

    // Create a new window
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "MLX Autorepeat Test");
    if (win_ptr == NULL)
    {
        mlx_destroy_display(mlx_ptr);
        free(mlx_ptr);
        fprintf(stderr, "Error: Failed to create window.\n");
        return 1;
    }

    // Enable key autorepeat
    mlx_do_key_autorepeaton(mlx_ptr);

    // Set up key press and key release event handlers
    mlx_hook(win_ptr, 2, 1L << 0, handle_keypress_test, NULL);
    mlx_hook(win_ptr, 3, 1L << 1, handle_keyrelease_test, NULL);

    // Enter the event loop
    mlx_loop(mlx_ptr);

    return 0;
}
