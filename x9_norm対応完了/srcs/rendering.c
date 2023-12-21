#include "../incs/minirt.h"

static t_color3	ft_init_color3(double r, double g, double b)
{
	t_color3	new;

	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
}

static void	ft_set_basis_vectors(t_ray *ray, t_camera camera)
{
	t_vec3 up_dir;

	up_dir = v_init(0, 1, 0);	//上方向
	ray->x_dir = v_cross(up_dir, camera.forward_dir);
	ray->y_dir = v_cross(camera.forward_dir, ray->x_dir);	//外積は引数の順番大事
	// カメラが真上と真下を向いている時はエッジケース
	if (camera.forward_dir.x == 0 && camera.forward_dir.y != 0 && camera.forward_dir.z == 0)
	{
		if (camera.forward_dir.y > 0)//これで2通りにわけないとハイライトの位置が変わる
		{
			ray->x_dir = v_init(-1, 0, 0);
			ray->y_dir = v_init(0, 0, -1);
		}
		else
		{
			ray->x_dir = v_init(1, 0, 0);
			ray->y_dir = v_init(0, 0, 1);
		}
	}
}

static void	ft_set_eye_ray(t_ray *ray, t_camera camera, int x, int y)
{
	double	dwidth;
	double	dheight;
	double	dx;
	double	dy;
	double	screen_distance;

	ft_set_basis_vectors(ray, camera);
	dwidth = 2.0;
	dheight = 2.0;
	if (WIDTH >= HEIGHT)
		dheight = 2.0 * HEIGHT / WIDTH;//2ではなく2.0にするの大事
	else
		dwidth = 2.0 * WIDTH / HEIGHT;
	dx = (dwidth * x)/(WIDTH - 1) - dwidth / 2;
	dy = (-dheight * y)/(HEIGHT - 1) + dheight / 2;
	screen_distance = WIDTH / 2 / tan(camera.degree / 2 * M_PI / 180);
	ray->pw = v_add(v_add(camera.camera_position, v_mult(camera.forward_dir, screen_distance)), v_add(v_mult(ray->x_dir, dx), v_mult(ray->y_dir, dy)));
	ray->start = camera.camera_position;
	ray->direction = v_sub(ray->pw, camera.camera_position);
}

static void	ft_set_color_of_pixel(t_rt *rt, int x, int y)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int 					int_color;

	r = 255 * constrain(rt->color.r, 0, 1);
	g = 255 * constrain(rt->color.g, 0, 1);
	b = 255 * constrain(rt->color.b, 0, 1);
	int_color = (r << 16) | (g << 8) | b;
	rt->pixel_index = (x * (rt->bit_per_pixel / 8)) + (y * rt->size_line);
	rt->pixel = (unsigned int *)(rt->pixel_addr + rt->pixel_index);
	*rt->pixel = int_color;
}

void ft_rendering(t_rt *rt)
{
	int	x;
	int	y;

	y = 0;
  while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			rt->color = ft_init_color3(0.0, 0.0, 0.0);//黒で初期化
			ft_set_eye_ray(&rt->ray, rt->scene.camera, x, y);
			ft_raytrace(rt);
			ft_set_color_of_pixel(rt, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img_ptr, 0, 0);
}
