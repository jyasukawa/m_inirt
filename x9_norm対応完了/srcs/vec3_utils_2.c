#include "../incs/minirt.h"

t_vec3	v_init(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	v_add(t_vec3 a, t_vec3 b)
{
	return (v_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	v_sub(t_vec3 a, t_vec3 b)
{
	return (v_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	v_mult(t_vec3 a, double b)
{
	return (v_init(a.x * b, a.y * b, a.z * b));
}
