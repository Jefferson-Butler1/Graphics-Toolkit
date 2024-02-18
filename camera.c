#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "camera.h"
#include "matrix.h"
#include "vector.h"
#include "trig.h"
#include "math.h"
#include "M3d_matrix_tools.h"

void make_camera_view_matrix(double out[4][4], double out_inverted[4][4], Camera cam){
    // This is hacky, probably good to rewrite this function to be better later
    M3d_view(out, out_inverted, (double *)&cam.eye, (double *)&cam.coi, (double *)&cam.up);
}

Vector3 to_camera_space(Vector3 point, Camera cam){
    double view_matrix[4][4];
    make_camera_view_matrix(view_matrix, NULL, cam);
    point = mat4_mult_point(point, view_matrix);
    return point;
}

Vector2 to_camera_screen_space(Vector3 point, Camera cam){    
    Vector2 screen_point;
    double film_distance = 1 / tan(to_radians(cam.half_fov_degrees));
    screen_point.x = point.x / point.z * film_distance;
    screen_point.y = point.y / point.z * film_distance;
    return screen_point;
}

Vector2 to_window_coordinates(Vector2 point, double width, double height){
    Vector2 window_coord;
    window_coord.x = (point.x * width / 2) + width / 2;
    window_coord.y = (point.y * height / 2) + height / 2;
    return window_coord;
}

void translate_camera(Camera* cam, Vector3 translation){
    cam->eye = vec3_add(cam->eye, translation);
    cam->coi = vec3_add(cam->coi, translation);
    cam->up = vec3_add(cam->up, translation);
}

bool visible_to_camera(Camera cam, Vector3 point){
    if(point.z < cam.near_clip_plane || point.z > cam.far_clip_plane){return false;}
    double half_angle_rads = to_radians(cam.half_fov_degrees);

    //TODO: make this work for non square aspect ratios
    double extent = point.z * tan(half_angle_rads);
    if(fabs(point.x) > extent){return false;}
    if(fabs(point.y) > extent){return false;}
    return true;
}