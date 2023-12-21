#include "../incs/minirt.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

double dot(const vector_t* a, const vector_t* b)
{
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

double squared_norm(const vector_t*v)
{
  return SQR(v->x) + SQR(v->y) + SQR(v->z);
}

double norm(const vector_t *v)
{
  return sqrt(squared_norm(v));
}

double normalize(vector_t* v)
{
  double vnorm = norm(v);
  v->x /= vnorm;
  v->y /= vnorm;
  v->z /= vnorm;
  return vnorm;
}

void cross(vector_t* o, const vector_t*a, const vector_t*b)
{
  o->x = a->y * b->z - a->z * b->y;
  o->y = a->z * b->x - a->x * b->z;
  o->z = a->x * b->y - a->y * b->x;
}

const char* vector_str(const vector_t*v)
{
  static char buf[1024];
  memset(buf, 0, sizeof(buf));
  sprintf((void*)buf, "(%f, %f, %f)", v->x, v->y, v->z);
  return buf;
}
