#include "../incs/minirt.h"

static int	ft_intersection_test(t_shape *shape, t_ray* ray, t_intersection_point* out_intp)
{
	if (shape->type == ST_SPHERE)
		return (ft_test_sphere(shape, ray, out_intp));
  else if (shape->type == ST_PLANE)
		return (ft_test_plane(shape, ray, out_intp));
	else if (shape->type == ST_CYLINDER)
		return (ft_test_cylinder(shape, ray, out_intp));
	return (0);
}

static void	ft_update(t_shape **nearest_shape, t_shape *shapes, t_intersection_point	*nearest_intp, t_intersection_point	intp)
{
	*nearest_shape = shapes;
	*nearest_intp = intp;
}

int	ft_get_nearest_shape(t_rt *rt, t_ray *ray, t_shape **out_shape, t_intersection_point *out_intp)
{
	ssize_t								i;
	t_shape								*nearest_shape;
	t_intersection_point	nearest_intp;
	int										res;
	t_intersection_point	intp;

	nearest_shape = NULL;
  nearest_intp.distance = DBL_MAX;//まずは一番大きく設定
	i = -1;
	while (++i < rt->scene.num_shapes)
	{
		res = ft_intersection_test(&rt->scene.shapes[i], ray, &intp);
		if (res != 0 && intp.distance < nearest_intp.distance)
			ft_update(&nearest_shape, &rt->scene.shapes[i], &nearest_intp, intp);
			// if (rt->flag == SHADOW) break;//ここだとshapes[0]が光源より遠いときに影がでなくなってしまう
	}
	if (nearest_shape != NULL)
	{
		if (out_shape != NULL && rt->flag != SHADOW)//shadow_rayの時はここでshapeの内容が書き換わるのを防ぐ
			*out_shape = nearest_shape;
		if (out_intp != NULL)
			*out_intp = nearest_intp;
		return (1);
	}
	else
		return (0);
}
