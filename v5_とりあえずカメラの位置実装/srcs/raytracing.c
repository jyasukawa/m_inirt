#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>
#include <stdio.h>
#include "../incs/minirt.h"

vector_t	v_init(float x, float y, float z)
{
	vector_t new;
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

vector_t	v_add(vector_t a, vector_t b)
{
	return (v_init(a.x + b.x, a.y + b.y, a.z + b.z));
}

vector_t	v_sub(vector_t a, vector_t b)
{
	return (v_init(a.x - b.x, a.y - b.y, a.z - b.z));
}

vector_t	v_mult(vector_t a, float b)
{
	return (v_init(a.x * b, a.y * b, a.z * b));
}

// ベクトルの外積
vector_t	v_cross(vector_t a, vector_t b)
{
	return (v_init(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x));
}

int raytrace(const scene_t *scene, const ray_t *eye_ray, colorf_t *out_col)
{
  /*1. 視線方向(eye_ray)の方向でもっとも近い物体を探す。*/
  int res;
  shape_t *shape;
  intersection_point_t intp;
  res = get_nearest_shape(scene, eye_ray, FLT_MAX, 0, &shape, &intp);
 
  if ( res /*視線方向に物体があった場合*/)
  {
     colorf_t col = {0,0,0}; /*色の計算結果を入れる変数*/
 
     /*2. 環境光の強さを計算してcolに入れる。 */
     col.r = scene->ambient_illuminance.r * shape->material.ambient_ref.r;
     col.g = scene->ambient_illuminance.g * shape->material.ambient_ref.g;
     col.b = scene->ambient_illuminance.b * shape->material.ambient_ref.b;

		const	light_t *light = &scene->lights[0];
		vector_t light_dir;
		float nl_dot;

		light_dir.x = light->vector.x - intp.position.x;
    light_dir.y = light->vector.y - intp.position.y;
    light_dir.z = light->vector.z - intp.position.z;
    vector_t light_tmp = light_dir;//正規化する前の入射ベクトルの大きさ等しい(下のdlで使う)
    normalize(&light_dir);

    float dl = norm(&light_tmp) - EPSILON;
    ray_t shadow_ray;
    shadow_ray.start = v_add(intp.position, v_mult(light_dir, EPSILON));
    shadow_ray.direction = light_dir;
    intersection_point_t tmp;
    int result = get_nearest_shape(scene, &shadow_ray, FLT_MAX, 1, &shape, &tmp);
    if (result == 0 || dl < tmp.distance)
    {
      nl_dot = dot(&light_dir, &intp.normal);
      nl_dot = CLAMP(nl_dot, 0, 1);

      col.r += shape->material.diffuse_ref.r * light->illuminance.r * nl_dot;
      col.g += shape->material.diffuse_ref.g * light->illuminance.g * nl_dot;
      col.b += shape->material.diffuse_ref.b * light->illuminance.b * nl_dot;

      if (nl_dot > 0)
      {
        vector_t ref_dir;
        vector_t inv_eye_dir;
        float vr_dot;
        float vr_dot_pow;

        ref_dir.x = 2 * nl_dot * intp.normal.x - light_dir.x;
        ref_dir.y = 2 * nl_dot * intp.normal.y - light_dir.y;
        ref_dir.z = 2 * nl_dot * intp.normal.z - light_dir.z;
        normalize(&ref_dir);

        inv_eye_dir.x = -1 * eye_ray->direction.x;
        inv_eye_dir.y = -1 * eye_ray->direction.y;
        inv_eye_dir.z = -1 * eye_ray->direction.z;
        normalize(&inv_eye_dir);

        vr_dot = dot(&inv_eye_dir, &ref_dir);
        vr_dot = CLAMP(vr_dot, 0, 1);
        vr_dot_pow = pow(vr_dot, shape->material.shininess);
        
        col.r += shape->material.specular_ref.r * light->illuminance.r * vr_dot_pow;
        col.g += shape->material.specular_ref.g * light->illuminance.g * vr_dot_pow;
        col.b += shape->material.specular_ref.b * light->illuminance.b * vr_dot_pow;
      }
    }
     *out_col = col;
 
     return 1;
  }
  else /*視線方向に物体がなかった場合*/
  {
     return 0;
  }
}/* int raytrace(const scene_t* scene, const ray_t *eye_ray, colorf_t *out_col) */

int intersection_test(const shape_t *shape, const ray_t* ray, 
                      intersection_point_t* out_intp)
{
  if ( shape->type == ST_SPHERE )
    {
      const sphere_t *sph = &shape->data.sphere;
      vector_t pe_pc;
      float A,B,C,D;
      float t;
      
      pe_pc.x = ray->start.x - sph->center.x;
      pe_pc.y = ray->start.y - sph->center.y;
      pe_pc.z = ray->start.z - sph->center.z;

      A = dot(&ray->direction, &ray->direction);
      B = 2 * dot(&ray->direction, &pe_pc);
      C = dot(&pe_pc, &pe_pc) - SQR(sph->radius);

      D = SQR(B) - 4*A*C;

      t = -1.0f;
      if ( D == 0 )
        {
          t = -B / (2*A);
        }
      else if ( D > 0 )
        {
          float t1 = (-B + sqrt(D))/(2*A);
          float t2 = (-B - sqrt(D))/(2*A);

          if ( t1 > 0 ) t = t1;
          if ( t2 > 0 && t2 < t ) t = t2;
        }

      if ( t > 0 )
        {
          if ( out_intp )
            {
              out_intp->distance = t;
              
              out_intp->position.x = ray->start.x + t * ray->direction.x;
              out_intp->position.y = ray->start.y + t * ray->direction.y;
              out_intp->position.z = ray->start.z + t * ray->direction.z;

              out_intp->normal.x = out_intp->position.x - sph->center.x;
              out_intp->normal.y = out_intp->position.y - sph->center.y;
              out_intp->normal.z = out_intp->position.z - sph->center.z;
              normalize(&out_intp->normal);
            }

          return 1;
        }
      else
        {
          return 0;
        }
    }
  else if ( shape->type == ST_PLANE )
    {
      const plane_t *pln = &shape->data.plane;
      float dn_dot = dot(&ray->direction, &pln->normal);

      if ( dn_dot != 0 )
        {
          vector_t s_p;
          float t;
          
          s_p.x = ray->start.x - pln->position.x;
          s_p.y = ray->start.y - pln->position.y;
          s_p.z = ray->start.z - pln->position.z;

          t = -dot(&s_p, &pln->normal) / dn_dot;

          if ( t > 0 )
            {
              if ( out_intp )
                {
                  out_intp->distance = t;

                  out_intp->position.x = ray->start.x + t * ray->direction.x;
                  out_intp->position.y = ray->start.y + t * ray->direction.y;
                  out_intp->position.z = ray->start.z + t * ray->direction.z;

                  out_intp->normal = pln->normal;
                }

              return 1;
            }
          else
            {
              return 0;
            }
        }
    }
    else if ( shape->type == ST_CYLINDER )
    {
      const cylinder_t *cylin = &shape->data.cylinder;
      vector_t dm = ray->direction;
      dm.y = 0;
      vector_t mm = v_sub(ray->start, cylin->position);
      mm.y = 0;

      float aa = squared_norm(&dm);//dot(&ray->direction, &ray->direction);と結果は同じ
      float bb = 2 * dot(&dm, &mm);
      float cc = squared_norm(&mm) - cylin->radius * cylin->radius;
      
      float dd = SQR(bb) - 4 * aa * cc;

      float tt = -1;

      if (dd == 0)
      {
        tt = -bb / (2*aa);
      }
      else if (dd > 0)
      {
        float t1 = (-bb + sqrt(dd))/(2*aa);
        float t2 = (-bb - sqrt(dd))/(2*aa);
        tt = t1 > 0 && t2 > 0 ? min(t1, t2) : max(t1, t2);
      }
      if (tt > 0)
      {
        if (out_intp)
        {
          out_intp->distance = tt;

          out_intp->position = v_add(ray->start, v_mult(ray->direction, tt));

          out_intp->normal.x = 2 * (out_intp->position.x - cylin->position.x);
          out_intp->normal.y = 0;
          out_intp->normal.z = 2 * (out_intp->position.z - cylin->position.z);
          normalize(&out_intp->normal);

          float hdist = sqrt(SQR(cylin->position.y - out_intp->position.y));

          if (hdist <= cylin->height / 2)
            return (1);
        }
      }
      else
        return (0);
    }
  return 0;
}/* int intersection_test(const shape_t *shape, const ray_t* ray,  */

int get_nearest_shape(const scene_t* scene, const ray_t *ray, float max_dist, int exit_once_found,
                      shape_t **out_shape, intersection_point_t *out_intp)
{
  size_t i;
  shape_t *nearest_shape = NULL;
  intersection_point_t nearest_intp;
  nearest_intp.distance = max_dist;

  for(i = 0; i < scene->num_shapes; ++i)
    {
      int res;
      intersection_point_t intp;
      
      res = intersection_test(&scene->shapes[i], ray, &intp);

      if ( res && intp.distance < nearest_intp.distance )
        {
          nearest_shape = &scene->shapes[i];
          nearest_intp = intp;
          if ( exit_once_found ) break;
        }
    }/* for */

  if ( nearest_shape )
    {
      if ( out_shape )
        *out_shape = nearest_shape;
      if ( out_intp )
        *out_intp = nearest_intp;
      
      return 1;
    }
  else
    {
      return 0;
    }
}


void init_shape(shape_t* shape, shape_type st, ...)
{
  va_list args;
  va_start(args, st);

  shape->type = st;
  if ( st == ST_SPHERE )
    {
      sphere_t* sph = &shape->data.sphere;
      
      sph->center.x = va_arg(args, double);
      sph->center.y = va_arg(args, double);
      sph->center.z = va_arg(args, double);
      sph->radius   = va_arg(args, double);
    }
  else if ( st == ST_PLANE )
    {
      plane_t* plane = &shape->data.plane;
      
      plane->position.x = va_arg(args, double);
      plane->position.y = va_arg(args, double);
      plane->position.z = va_arg(args, double);

      plane->normal.x = va_arg(args, double);
      plane->normal.y = va_arg(args, double);
      plane->normal.z = va_arg(args, double);
    }
    else if (st == ST_CYLINDER)
    {
      cylinder_t *cylin = &shape->data.cylinder;

      cylin->position.x = va_arg(args, double);
      cylin->position.y = va_arg(args, double);
      cylin->position.z = va_arg(args, double);
      cylin->radius     = va_arg(args, double);
      cylin->height     = va_arg(args, double);
    }
  else
    {
      fprintf(stderr, "init_shape : unknown shape type.\n");
      abort();
    }
  
  va_end(args);
}

void init_material(material_t* mat,
		   float ambR, float ambG, float ambB,
		   float difR, float difG, float difB,
		   float speR, float speG, float speB,
		   float shns)
{
  SET_COLOR(mat->ambient_ref,  ambR, ambG, ambB);
  SET_COLOR(mat->diffuse_ref,  difR, difG, difB);
  SET_COLOR(mat->specular_ref, speR, speG, speB);
  mat->shininess = shns;
}

void init_light(light_t* light, light_type lt,
		float vx, float vy, float vz,
		float illR, float illG, float illB)
{
  light->type = lt;
  SET_VECTOR(light->vector, vx, vy, vz);
  SET_COLOR(light->illuminance, illR, illG, illB);
}
