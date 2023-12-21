#include "../incs/minirt.h"

void	init_ambient(t_ambient *ambient, double amb_r, int r, int g, int b)
{
  ambient->ambient_ref = amb_r;
	ambient->amb_illuminance.r = (double)r / 255.0;
	ambient->amb_illuminance.g = (double)g / 255.0;
	ambient->amb_illuminance.b = (double)b / 255.0;
}

void	init_camera(t_camera *camera, double vx, double vy, double vz, double nx, double ny, double nz, double fov)
{
  camera->camera_position = v_init(vx, vy, vz);
  camera->forward_dir = v_init(nx, ny, nz);
  camera->degree = fov;
}

void	init_light(t_light *light, double vx, double vy, double vz, double spe_r, int r, int g, int b)
{
  light->vector = v_init(vx, vy, vz);
  light->specular_ref = spe_r;
	light->illuminance.r = (double)r / 255.0;
	light->illuminance.g = (double)g / 255.0;
	light->illuminance.b = (double)b / 255.0;
}

void	init_shape(t_shape *shape, t_shape_type st, ...)
{
	va_list args;
	va_start(args, st);

	shape->type = st;
	if (st == ST_SPHERE)
	{
		t_sphere* sph = &shape->u_data.sphere;
		
		sph->center.x = va_arg(args, double);
		sph->center.y = va_arg(args, double);
		sph->center.z = va_arg(args, double);
		sph->radius   = va_arg(args, double);
		shape->diffuse_ref.r = va_arg(args, int) / 255.0;
		shape->diffuse_ref.g = va_arg(args, int) / 255.0;
		shape->diffuse_ref.b = va_arg(args, int) / 255.0;
	}
	else if (st == ST_PLANE)
	{
		t_plane* plane = &shape->u_data.plane;
		
		plane->position.x = va_arg(args, double);
		plane->position.y = va_arg(args, double);
		plane->position.z = va_arg(args, double);
		plane->normal.x = va_arg(args, double);
		plane->normal.y = va_arg(args, double);
		plane->normal.z = va_arg(args, double);
		shape->diffuse_ref.r = va_arg(args, int) / 255.0;
		shape->diffuse_ref.g = va_arg(args, int) / 255.0;
		shape->diffuse_ref.b = va_arg(args, int) / 255.0;
	}
	else if (st == ST_CYLINDER)
	{
		t_cylinder *cylin = &shape->u_data.cylinder;

		cylin->position.x = va_arg(args, double);
		cylin->position.y = va_arg(args, double);
		cylin->position.z = va_arg(args, double);
		cylin->radius     = va_arg(args, double);
		cylin->height     = va_arg(args, double);
		cylin->normal.x = va_arg(args, double);
		cylin->normal.y = va_arg(args, double);
		cylin->normal.z = va_arg(args, double);
		shape->diffuse_ref.r = va_arg(args, int) / 255.0;
		shape->diffuse_ref.g = va_arg(args, int) / 255.0;
		shape->diffuse_ref.b = va_arg(args, int) / 255.0;
	}
	else
	{
		fprintf(stderr, "init_shape : unknown shape type.\n");
		abort();
	}
	va_end(args);
}

void	ft_init_scene(char *file, t_scene *scene)
{
	(void)file;
	scene->num_shapes = 5;
	scene->shapes = malloc(sizeof(t_shape) * scene->num_shapes);//メモリ確保(失敗した時のfree,exit処理必要)

	//必ず実数を渡すこと．間違って整数を渡すとうまく動かない(RGBは0-255のint?)
	init_ambient(&scene->ambient, 0.20,//環境光係数(RGB)
											255, 255, 255);//環境光の強さ

	init_camera(&scene->camera, 50, 20, -5,//カメラ位置
											-0.92, -0.37, 0.09,//カメラの向き
																	179.3);//カメラの視野角

	init_light(&scene->light, -30.0, 70.0, -50.0,//点光源の位置
																					0.30,//鏡面反射率
																255, 255, 255);//点光源の照度(色)

	init_shape(&scene->shapes[0], ST_SPHERE,
												-10.0, 3.0, -3.0,//球の中心位置
																			7.0,//球の半径
														177, 177, 0);//拡散反射係数(RGB)

	init_shape(&scene->shapes[1], ST_PLANE,
													0.0, -2.0, 0.0,//平面が通る点の位置
														0.0, 1.0, 0.0,//平面の法線ベクトル
															177, 0, 0);//拡散反射係数(RGB)

	init_shape(&scene->shapes[2], ST_PLANE,
													0.0, 0.0, 10.0,//平面が通る点の位置
														0.0, 0.0, 1.0,//平面の法線ベクトル
															0, 177, 0);//拡散反射係数(RGB)

	// init_shape(&scene->shapes[3], ST_PLANE,
	// 											-100.0, 0.0, 0.0,//平面が通る点の位置
	// 													1.0, 0.0, 0.0,//平面の法線ベクトル
	// 														0, 0, 177);//拡散反射係数(RGB)

	init_shape(&scene->shapes[4], ST_CYLINDER,
													-3.0, 15.0, -15.0,//中心位置
																				5.0,//半径
																				10.0,//高さ
															0.0, 1.0, 0.0,//平面の法線ベクトル
																177, 177, 0);//拡散反射係数(RGB)
}
