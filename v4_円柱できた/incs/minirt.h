#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>

#define SQR(x) ((x)*(x))
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)


# define WIDTH 512
# define HEIGHT 512

# define ESC 53

# define EPSILON (1.0/512)

typedef struct {
  float x,y,z;
} vector_t;

typedef struct	s_rt
{
	void					*mlx_ptr;
	void					*win_ptr;
	void					*img_ptr;
	char					*pixel_addr;
	int						size_line;
	int						bit_per_pixel; 
	int						endian;
}								t_rt;
#define SET_COLOR(col, r_, g_, b_) { col.r = r_; col.g = g_; col.b = b_; }
#define SET_VECTOR(vec, x_, y_, z_) { vec.x = x_; vec.y = y_; vec.z = z_; }

typedef struct
{
  float r,g,b;
} colorf_t;

typedef struct
{
  vector_t start;     /* 始点 */
  vector_t direction; /* 方向ベクトル */
} ray_t;

typedef struct
{
  vector_t center; /* 球の中心 */
  float radius;    /* 球の半径 */
} sphere_t;

typedef struct
{
  vector_t normal;   /* 法線ベクトル */
  vector_t position; /* 面が通る点の位置ベクトル */
} plane_t;

typedef struct
{
  vector_t position; /* 位置 */
  float radius;      /* 半径 */
  float height;      /* 高さ */
}  cylinder_t;

typedef struct
{
  colorf_t ambient_ref;   /* 環境光反射率(RGB) */
  colorf_t diffuse_ref;   /* 拡散反射率(RGB) */
  colorf_t specular_ref;  /* 鏡面反射率(RGB) */
  float shininess;        /* 光沢度 */
} material_t;

typedef enum
  {
    ST_SPHERE, /* 球 */
    ST_PLANE,   /* 平面 */
    ST_CYLINDER /* 【追加】円柱 */
  } shape_type;
typedef struct
{
  shape_type type;     /* 球 or 平面 */
  union
  {
    sphere_t sphere;   /* 球の情報 */
    plane_t plane;     /* 平面の情報 */
    cylinder_t cylinder; /* 【追加】円柱 */
  } data;

  material_t material; /* 物体表面の質感 */
} shape_t;


typedef enum
  {
    LT_POINT,      /* 点光源 */
    LT_DIRECTIONAL/* 平行光源 */
  } light_type;
typedef struct
{
  light_type type;      /* 点光源 or 平行光源 */
  vector_t vector;      /* 光源位置 or 公選法光 */
  colorf_t illuminance; /* 照度(RGB) */
} light_t;

typedef struct
{
  shape_t *shapes;              /* 物体リストへのポインタ */
  size_t num_shapes_capacity;   /* 物体リストの最大格納数 */
  size_t num_shapes;            /* 物体リストに実際に格納されている数 */
  light_t *lights;              /* 光源リストへのポインタ */
  size_t num_lights_capacity;   /* 光源リストの最大格納数 */
  size_t num_lights;            /* 光源リストに実際に格納されている数 */
  colorf_t ambient_illuminance; /* 環境光の強さ(RGB) */
} scene_t;


typedef struct
{
  float distance;      /* 交点までの距離 */
  vector_t position;   /* 交点の位置ベクトル */
  vector_t normal;     /* 交点における物体表面の法線ベクトル */
} intersection_point_t;

int intersection_test(const shape_t *shape, const ray_t* ray, intersection_point_t* out_intp);
int get_nearest_shape(const scene_t* scene, const ray_t *ray, float max_dist, int exit_once_found,
                      shape_t **out_shape, intersection_point_t *out_intp);
int raytrace(const scene_t* scene, const ray_t *eye_ray, colorf_t *out_col);

void init_shape(shape_t* shape, shape_type st, ...);
void init_material(material_t* mat,
		   float ambR, float ambG, float ambB,
		   float difR, float difG, float difB,
		   float speR, float speG, float speB,
		   float shns);
void init_light(light_t* light, light_type lt,
		float vx, float vy, float vz,
		float illR, float illG, float illB);
// minirt_utils.c
int	ft_clean_up_and_exit(t_rt *rt);

// draw.c
void	ft_draw(t_rt *rt);
float dot(const vector_t* a, const vector_t* b);
float squared_norm(const vector_t*v);

float norm(const vector_t *v);
float normalize(vector_t* v);

void cross(vector_t* o, const vector_t*a, const vector_t*b);

const char* vector_str(const vector_t*v);

void scene_setting(scene_t *scene);

double min(double a, double b);
double max(double a, double b);

#endif