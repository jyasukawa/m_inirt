#include "../incs/minirt.h"

static void	ft_add_ambient_color(t_scene scene, t_color3 *color)
{
	color->r += scene.ambient.ambient_ref * scene.ambient.amb_illuminance.r;
	color->g += scene.ambient.ambient_ref * scene.ambient.amb_illuminance.g;
	color->b += scene.ambient.ambient_ref * scene.ambient.amb_illuminance.b;
}

static void	ft_add_diffuse_color(t_scene scene, t_shape *shape, double nl_dot, t_color3 *color)
{
	color->r += shape->diffuse_ref.r * scene.light.illuminance.r * nl_dot;
	color->g += shape->diffuse_ref.g * scene.light.illuminance.g * nl_dot;
	color->b += shape->diffuse_ref.b * scene.light.illuminance.b * nl_dot;
}

static void	ft_add_specular_color(t_scene scene, double vr_dot_pow, t_color3 *color)
{
	color->r += scene.light.specular_ref * scene.light.illuminance.r * vr_dot_pow;
	color->g += scene.light.specular_ref * scene.light.illuminance.g * vr_dot_pow;
	color->b += scene.light.specular_ref * scene.light.illuminance.b * vr_dot_pow;
}

static void	ft_add_light_ref_color(t_rt *rt, t_shape *shape, t_intersection_point intp, t_vec3 light_dir)
{
	double nl_dot;
	t_vec3 ref_dir;
	t_vec3 inv_eye_dir;
	double vr_dot;
	double vr_dot_pow;

	nl_dot = v_dot(light_dir, intp.normal);
	nl_dot = constrain(nl_dot, 0, 1);
	ft_add_diffuse_color(rt->scene, shape, nl_dot, &rt->color);
	if (nl_dot > 0)
	{
		ref_dir = v_sub(v_mult(intp.normal, 2 * nl_dot), light_dir);
		ref_dir = v_normalize(ref_dir);
		inv_eye_dir = v_mult(rt->ray.direction, -1);
		inv_eye_dir = v_normalize(inv_eye_dir);
		vr_dot = v_dot(inv_eye_dir, ref_dir);
		vr_dot = constrain(vr_dot, 0, 1);
		vr_dot_pow = pow(vr_dot, SHININESS);
		ft_add_specular_color(rt->scene, vr_dot_pow, &rt->color);
	}
}

void	ft_raytrace(t_rt *rt)
{
	t_shape 							*shape;
	t_intersection_point	intp;
	t_vec3 								light_dir;
	double 								dl;
	t_intersection_point	tmp;

	rt->flag = ft_get_nearest_shape(rt, &rt->ray, &shape, &intp);//視線方向(ray)の方向でもっとも近い物体を探す
	if (rt->flag == 0)//視線方向に物体がなかった場合はここでreturn
		return ;
  ft_add_ambient_color(rt->scene, &rt->color);//環境光の強さを計算してcolに入れる
	light_dir = v_sub(rt->scene.light.vector, intp.position);
	dl = v_norm(light_dir) - EPSILON;//正規化する前の入射ベクトルの大きさを代入
	light_dir = v_normalize(light_dir);
	rt->shadow_ray.start = v_add(intp.position, v_mult(light_dir, EPSILON));
	rt->shadow_ray.direction = light_dir;
	rt->flag = SHADOW;
	rt->flag = ft_get_nearest_shape(rt, &rt->shadow_ray, &shape, &tmp);
	if (rt->flag == 0 || dl < tmp.distance)
		ft_add_light_ref_color(rt, shape, intp, light_dir);
}
