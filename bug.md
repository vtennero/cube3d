AddressSanitizer:DEADLYSIGNAL
=================================================================
==730177==ERROR: AddressSanitizer: SEGV on unknown address 0x7fa1ad132500 (pc 0x55e02ee3370a bp 0x7ffce6be2350 sp 0x7ffce6be22c0 T0)
==730177==The signal is caused by a READ memory access.
    #0 0x55e02ee3370a in get_pixel_color (/goinfre/cliew/cub3d/cub3D_bonus+0x2c70a)
    #1 0x55e02ee32e98 in draw_sprite_stripe (/goinfre/cliew/cub3d/cub3D_bonus+0x2be98)
    #2 0x55e02ee3afae in render_single_sprite (/goinfre/cliew/cub3d/cub3D_bonus+0x33fae)
    #3 0x55e02ee36a2c in render_eagle_sprites (/goinfre/cliew/cub3d/cub3D_bonus+0x2fa2c)
    #4 0x55e02ee35c60 in render_ongoing_eagle (/goinfre/cliew/cub3d/cub3D_bonus+0x2ec60)
    #5 0x55e02ee35d5f in render_eagle_strike (/goinfre/cliew/cub3d/cub3D_bonus+0x2ed5f)
    #6 0x55e02ee359ca in run_bonus_rendering (/goinfre/cliew/cub3d/cub3D_bonus+0x2e9ca)
    #7 0x55e02ee35792 in bonus_game_loop_3 (/goinfre/cliew/cub3d/cub3D_bonus+0x2e792)
    #8 0x55e02ee35155 in bonus_game_loop (/goinfre/cliew/cub3d/cub3D_bonus+0x2e155)
    #9 0x55e02ee2e1b7 in render (/goinfre/cliew/cub3d/cub3D_bonus+0x271b7)
    #10 0x55e02ee4bfbc in mlx_loop (/goinfre/cliew/cub3d/cub3D_bonus+0x44fbc)
    #11 0x55e02ee2e27a in setup_game_mlx (/goinfre/cliew/cub3d/cub3D_bonus+0x2727a)
    #12 0x55e02ee20c15 in initgame (/goinfre/cliew/cub3d/cub3D_bonus+0x19c15)
    #13 0x55e02ee49bb5 in main (/goinfre/cliew/cub3d/cub3D_bonus+0x42bb5)
    #14 0x7fa1b4145d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #15 0x7fa1b4145e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #16 0x55e02ee13e24 in _start (/goinfre/cliew/cub3d/cub3D_bonus+0xce24)
