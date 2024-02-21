#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parametric.h"
#include "matrix.h"
#include "camera.h"
#include "lightmodel.h"
#include "FPToolkit.h"

static int WIDTH;
static int HEIGHT;

double NORMAL_DELTA = 0.001;

void init_window(int width, int height){
    WIDTH = width;
    HEIGHT = height;
    G_init_graphics(width, height);
}

void draw_parametric_object_3d(ParametricObject3D object,
                            Camera cam,
                            PhongLight* lights,
                            int num_lights,
                            int width, int height,
                            double z_buffer[width][height],
                            enum ViewMode mode)
{
    for(double u = object.u_start; u < object.u_end; u += object.u_step){
        for(double v = object.v_start; v < object.v_end; v += object.v_step){
            Vector3 point = mat4_mult_point(object.f(u, v), object.transform);

            Vector3 camera_point = to_camera_space(point, cam);
            if(!is_visible_to_camera(cam, camera_point)) continue; //Cull point if not visible
            
            double normalized_z_dist = (camera_point.z - cam.near_clip_plane) / (cam.far_clip_plane - cam.near_clip_plane);
            Vector2 pixel_location = to_window_coordinates(to_camera_screen_space(camera_point, cam), width, height);

            if(normalized_z_dist >  z_buffer[(int)pixel_location.x][(int)pixel_location.y]) continue;

            z_buffer[(int)pixel_location.x][(int)pixel_location.y] = normalized_z_dist;

            if(mode == UNLIT){
                G_rgb(object.material.base_color.x, object.material.base_color.y, object.material.base_color.z);
            } else if(mode == Z_BUFF){
                double brightness = z_buffer[(int)pixel_location.x][(int)pixel_location.y];
                G_rgb(brightness, brightness, brightness);
            } else{
                /* Do lighting calculations */
                Vector3 tangent_a = vec3_normalized(vec3_sub(mat4_mult_point(object.f(u, v + NORMAL_DELTA), object.transform), point));
                Vector3 tangent_b = vec3_normalized(vec3_sub(mat4_mult_point(object.f(u + NORMAL_DELTA, v), object.transform), point));
                Vector3 normal = vec3_cross_prod(tangent_a, tangent_b);
                if(mode == NORMAL){
                    G_rgb(normal.x, normal.y, normal.z);
                } else if (mode == LIT){
                    Vector3 col = phong_lighting(point, normal, cam, object.material, lights, num_lights);
                    G_rgb(col.x, col.y, col.z);
                }
            }

            G_pixel(pixel_location.x, pixel_location.y);
        }
    }
}