#include "cube3d.h"

// int main(void)
// {
// 	void    *mlx_ptr;
// 	void    *win_ptr;

// 	mlx_ptr = mlx_init();
// 	if (!mlx_ptr)
// 		return (1);
// 	win_ptr = mlx_new_window (mlx_ptr, 300, 300, "Hello World");
// 	if (!win_ptr)
// 		return (2);
// 	mlx_loop(mlx_ptr);
// 	return (0);
// }


// #include <mlx.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook! %d\n", keycode);
	(void)vars;
	return (0);
}

int	mouse_hook(int keycode, t_vars *vars)
{
	printf("Hello from mouse_hook! %d\n", keycode);
	(void)vars;
	return (0);
}

int	main(void)
{
	t_vars	vars;

	printf("Hello this is bonus!\n");
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
}
