#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "../incs/minirt.h"

#define WIDTH 512
#define HEIGHT 512

// void scene_setting(scene_t *scene); /* forward */

// int main()
// {
//   int y,x;                            /* スクリーン座標 */
//   unsigned char r,g,b;                /* 画素値(RGB) */
//   scene_t scene;
//   vector_t eye_pos    = { 0, 0, -5 }; /* 視点位置 */
//   vector_t pw;                        /* 三次元空間でのスクリーン座標 */

//   scene_setting(&scene);
  
//   printf("P3\n");
//   printf("%d %d\n", WIDTH, HEIGHT);
//   printf("255\n");

//   pw.z = 0; /* スクリーンのz座標は常にゼロ */
  
//   for(y = 0; y < HEIGHT; ++y)
//     {
//       pw.y = (-2.0f * y)/(HEIGHT-1) + 1.0f;
//       for(x = 0; x < WIDTH; ++x)
//         {
//           ray_t eye_ray;
//           colorf_t col = {100/255.0, 149/255.0, 237/255.0};
          
//           pw.x = (2.0f * x)/(WIDTH-1 ) - 1.0f;

//           eye_ray.start = eye_pos;
//           eye_ray.direction.x = pw.x - eye_pos.x;
//           eye_ray.direction.y = pw.y - eye_pos.y;
//           eye_ray.direction.z = pw.z - eye_pos.z;

//           raytrace(&scene, &eye_ray, &col);

//           r = 255 * CLAMP(col.r, 0, 1);
//           g = 255 * CLAMP(col.g, 0, 1);
//           b = 255 * CLAMP(col.b, 0, 1);

//           printf("%d %d %d\n", r, g, b);
          
//         }/* for */
//     }/* for */

//   free(scene.lights);
//   free(scene.shapes);

//   return 0;
  
// }/* int main() */
