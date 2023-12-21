#include "../incs/minirt.h"

// ベクトルの内積
double	v_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// ベクトルの外積
t_vec3	v_cross(t_vec3 a, t_vec3 b)
{
	return (v_init(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x));
}

// ベクトルのノルム(長さ)
double	v_norm(t_vec3 v)
{
  return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

// ベクトルの正規化
t_vec3	v_normalize(t_vec3 v)
{
	double norm;

	norm = v_norm(v);
	v.x = v.x / norm;
	v.y = v.y / norm;
	v.z = v.z / norm;
	return (v_init(v.x, v.y, v.z));
}
