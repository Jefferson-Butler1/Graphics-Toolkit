#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "camera.h"
#include "scope.h"
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

//TODO: make this work for non square aspect ratios
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

void transform_camera(Camera* cam, double transform[4][4]){
    cam->eye = mat4_mult_point(cam->eye, transform);
    cam->coi = mat4_mult_point(cam->coi, transform);
    cam->up  = mat4_mult_point(cam->up, transform);
}

void translate_camera(Camera* cam, Vector3 translation, enum TransformScope scope){
    if(scope == LOCAL){
        printf("Local transform not implemented\n");
        return;
    }
    cam->eye = vec3_add(cam->eye, translation);
    cam->coi = vec3_add(cam->coi, translation);
    cam->up = vec3_add(cam->up, translation);
}
//TODO: Make these rotations along the local axis(optionally)
void rotate_camera_x_degrees(Camera* cam, double x_degrees, enum TransformScope scope){
    if(scope == LOCAL){
        printf("Local transform not implemented\n");
        return;
    }
    double rads = to_radians(x_degrees);
    double translation[4][4];
    double rotation[4][4];

    M3d_make_x_rotation_cs(rotation, cos(rads), sin(rads));
    M3d_make_translation(translation, -cam->eye.x, -cam->eye.y, -cam->eye.z);
    M3d_mat_mult(rotation, rotation, translation);
    M3d_make_translation(translation, cam->eye.x, cam->eye.y, cam->eye.z);
    M3d_mat_mult(rotation, translation, rotation);
    
    transform_camera(cam, rotation);
}

void rotate_camera_y_degrees(Camera* cam, double y_degrees, enum TransformScope scope){
    if(scope == LOCAL){
        printf("Local transform not implemented\n");
        return;
    }
    double rads = to_radians(y_degrees);
    double translation[4][4];
    double rotation[4][4];

    M3d_make_y_rotation_cs(rotation, cos(rads), sin(rads));
    M3d_make_translation(translation, -cam->eye.x, -cam->eye.y, -cam->eye.z);
    M3d_mat_mult(rotation, rotation, translation);
    M3d_make_translation(translation, cam->eye.x, cam->eye.y, cam->eye.z);
    M3d_mat_mult(rotation, translation, rotation);
    
    transform_camera(cam, rotation);
}

void rotate_camera_z_degrees(Camera* cam, double z_degrees, enum TransformScope scope){
    if(scope == LOCAL){
        printf("Local transform not implemented\n");
        return;
    }
    double rads = to_radians(z_degrees);
    double translation[4][4];
    double rotation[4][4];

    M3d_make_z_rotation_cs(rotation, cos(rads), sin(rads));
    M3d_make_translation(translation, -cam->eye.x, -cam->eye.y, -cam->eye.z);
    M3d_mat_mult(rotation, rotation, translation);
    M3d_make_translation(translation, cam->eye.x, cam->eye.y, cam->eye.z);
    M3d_mat_mult(rotation, translation, rotation);

    transform_camera(cam, rotation);
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