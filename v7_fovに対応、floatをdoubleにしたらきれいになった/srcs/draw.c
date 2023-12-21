#include "../incs/minirt.h"

typedef struct	s_vec3 {
	double		x;
	double		y;
	double		z;
} t_vec3;

t_vec3	vec3_init(double x, double y, double z)
{
	t_vec3 new;
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

//内積
double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// ベクトルの外積
t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x));
}

t_vec3	vec3_mult(t_vec3 a, double b)
{
	return (vec3_init(a.x * b, a.y * b, a.z * b));
}

// ベクトルのノルム(長さ)
double	vec3_mag(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

// ベクトルの正規化
t_vec3	vec3_normalize(t_vec3 a)
{
	double mag = vec3_mag(a);
	return (vec3_init(a.x / mag, a.y / mag, a.z / mag));
}

// 最小値を返す関数
double min(double a, double b) {
    return (a < b) ? a : b;
}
// 最大値を返す関数
double max(double a, double b) {
    return (a > b) ? a : b;
}
//constrain 関数をC言語で実装した例
double constrain(double v, double vmin, double vmax) {
    if (v < vmin) {
        return vmin;
    } else if (v > vmax) {
        return vmax;
    } else {
        return v;
    }
}

void ft_draw(t_rt *rt)
{
	scene_t scene;
	scene.eye_position = v_init(0, 4, -300);
	scene.look_at = v_init(0, 0, 5);

	double degree = 90;
	scene.screen_distance = rt->screen_width / 2 / tan(degree / 2 * M_PI / 180);
	printf("%f\n", scene.screen_distance);

	vector_t up_dir = {0, 1, 0};// 上方向
	vector_t forward_dir = v_sub(scene.look_at, scene.eye_position);
	normalize(&forward_dir);
	vector_t x_dir = v_cross(up_dir, forward_dir);
	vector_t y_dir = v_cross(forward_dir, x_dir);//外積は引数の順番大事

	int y,x;
	int color;                            /* スクリーン座標 */
  unsigned char r,g,b;                /* 画素値(RGB) */

  scene_setting(&scene);

	// rt->screen_height = 400;
	// rt->screen_width = 600;

	double fwidth = 2.0;
	double fheight = 2.0;
	if (rt->screen_width >= rt->screen_height)
		fheight = 2.0 * rt->screen_height / rt->screen_width;//2ではなく2.0にするの大事
	else
		fwidth = 2.0 * rt->screen_width / rt->screen_height;
  for(y = 0; y < rt->screen_height; ++y)
	{
		double fy = (-fheight * y)/(rt->screen_height - 1) + fheight / 2;
		for(x = 0; x < rt->screen_width; ++x)
			{
				ray_t eye_ray;
				colorf_t col = {100.0, 100.0, 100.0};
				
				double fx = (fwidth * x)/(rt->screen_width - 1) - fwidth / 2;

				vector_t pw = v_add(v_add(scene.eye_position, v_mult(forward_dir,scene.screen_distance)), v_add(v_mult(x_dir, fx), v_mult(y_dir, fy)));

				eye_ray.start = scene.eye_position;
				eye_ray.direction.x = pw.x - scene.eye_position.x;
				eye_ray.direction.y = pw.y - scene.eye_position.y;
				eye_ray.direction.z = pw.z - scene.eye_position.z;

				raytrace(&scene, &eye_ray, &col);

				r = 255 * CLAMP(col.r, 0, 1);
				g = 255 * CLAMP(col.g, 0, 1);
				b = 255 * CLAMP(col.b, 0, 1);
				
				color = (r << 16) | (g << 8) | b;

				int pixel_index = (x * (rt->bit_per_pixel / 8)) + (y * rt->size_line);
				unsigned int *pixel = (unsigned int *)(rt->pixel_addr + pixel_index);
				*pixel = color;
			}/* for */
	}/* for */
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img_ptr, 0, 0);
}
