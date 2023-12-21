#include "../incs/minirt.h"

static void	ft_init_rt(t_rt *rt)
{
	rt->mlx_ptr = mlx_init();
	if (rt->mlx_ptr == NULL)
		ft_clean_up_and_exit(rt);
	rt->win_ptr = mlx_new_window(rt->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (rt->win_ptr == NULL)
		ft_clean_up_and_exit(rt);
	rt->img_ptr = mlx_new_image(rt->mlx_ptr, WIDTH, HEIGHT);
	if (rt->img_ptr == NULL)
		ft_clean_up_and_exit(rt);
	rt->pixel_addr = mlx_get_data_addr(rt->img_ptr, &rt->bit_per_pixel, &rt->size_line, &rt->endian);
	if (rt->pixel_addr == NULL)
		ft_clean_up_and_exit(rt);
}

static int	ft_deal_key(int key_code, t_rt *rt)
{
	if (key_code == ESC)
		ft_clean_up_and_exit(rt);
	return (0);
}

int	main(int argc, char **argv)
{
	t_rt	rt;

	(void)argc;
	// if (argc != 2)
	// 	exit(1);	//error_message
	rt = (t_rt){0};
	ft_init_scene(argv[1], &rt.scene);//ここで.rtファイルの読み込み、エラーハンドリング
	ft_init_rt(&rt);
	ft_rendering(&rt);
	mlx_hook(rt.win_ptr, 2, 0, ft_deal_key, &rt);
	mlx_hook(rt.win_ptr, 17, 0, ft_clean_up_and_exit, &rt);
	mlx_loop(rt.mlx_ptr);
	exit(0);
}
