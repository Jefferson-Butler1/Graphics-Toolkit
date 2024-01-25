#include "vector.h"
#include <math.h>
#include <stdio.h>


/* 3D Vector Functions */
double vec3_magnitude(Vector3 v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

void vec3_normalize(Vector3 *v){
    double magnitude = vec3_magnitude(*v);
    v->x /= magnitude;
    v->y /= magnitude;
    v->z /= magnitude;
}

Vector3 vec3_normalized(Vector3 v){
    double magnitude = vec3_magnitude(v);
    Vector3 result;
    result.x = v.x / magnitude;
    result.y = v.y / magnitude;
    result.z = v.z / magnitude;
    return result;
}

Vector3 vec3_add(Vector3 a, Vector3 b){
    Vector3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

Vector3 vec3_sub(Vector3 a, Vector3 b){
    Vector3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

Vector3 vec3_mult(Vector3 a, Vector3 b){
    Vector3 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    return result;
}

Vector3 vec3_div(Vector3 a, Vector3 b){
    Vector3 result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;
    return result;
}

/* 2D Vector Functions */

double vec2_magnitude(Vector2 v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

void vec2_normalize(Vector2 *v){
    double magnitude = vec2_magnitude(*v);
    v->x /= magnitude;
    v->y /= magnitude;
}

Vector2 vec2_normalized(Vector2 v){
    double magnitude = vec2_magnitude(v);
    Vector2 result;
    result.x = v.x / magnitude;
    result.y = v.y / magnitude;
    return result;
}

Vector2 vec2_add(Vector2 a, Vector2 b){
    Vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

Vector2 vec2_sub(Vector2 a, Vector2 b){
    Vector2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

Vector2 vec2_mult(Vector2 a, Vector2 b){
    Vector2 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    return result;
}

Vector2 vec2_div(Vector2 a, Vector2 b){
    Vector2 result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    return result;
}

Vector2 vec2_scale(Vector2 v, double scale){
    Vector2 result;
    result.x = v.x * scale;
    result.y = v.y * scale;
    return result;
}


