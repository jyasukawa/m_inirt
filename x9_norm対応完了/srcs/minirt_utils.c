#include "../incs/minirt.h"

int	ft_clean_up_and_exit(t_rt *rt)//ここにfree処理なども追加
{
	if (rt->img_ptr != NULL)
		mlx_destroy_image(rt->mlx_ptr, rt->img_ptr);
	if (rt->win_ptr != NULL)
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
	if (rt->win_ptr != NULL)
		mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	exit(1);
	return (0);// mlx_hookの引数に渡すためにint型にしてある
}
