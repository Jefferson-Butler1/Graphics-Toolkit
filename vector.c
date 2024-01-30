#include "vector.h"

#include <math.h>
#include <stdio.h>

/* 3D Vector Functions */
double vec3_magnitude(Vector3 v) {
  return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));

  void vec3_print(Vector3 v) { printf("<%lf, %lf, %lf>\n", v.x, v.y, v.z); }

  double vec3_magnitude(Vector3 v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
  }

  void vec3_normalize(Vector3 * v) {
    double magnitude = vec3_magnitude(*v);
    v->x /= magnitude;
    v->y /= magnitude;
    v->z /= magnitude;
  }

  Vector3 vec3_normalized(Vector3 v) {
    double magnitude = vec3_magnitude(v);
    Vector3 result;
    result.x = v.x / magnitude;
    result.y = v.y / magnitude;
    result.z = v.z / magnitude;
    return result;
  }

  Vector3 vec3_add(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
  }

  Vector3 vec3_sub(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
  }

  Vector3 vec3_mult(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    return result;
  }

  Vector3 vec3_div(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;
    return result;
  }

  Vector3 vec3_cross_prod(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = (a.y * b.z) - (b.y * a.z);
    result.y = (a.x * b.z) - (b.x * a.z);
    result.z = (a.x * b.y) - (b.x * a.y);
    return result;
  }
  Vector3 vec3_new(double x, double y, double z) {
    Vector3 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
  }

  Vector3 *vec3_create_list(double x[], double y[], double z[], int n) {
    Vector3 res[n];
    for (int i = 0; i < n; i++) {
      res[i] = vec3_new(x[i], y[i], z[i]);
    }
    return res;
  }

  /* 2D Vector Functions */

  void vec2_print(Vector2 v) { printf("<%lf, %lf>\n", v.x, v.y); }

  void vec2_print(Vector2 v) { printf("<%lf, %lf>\n", v.x, v.y); }

  double vec2_magnitude(Vector2 v) { return sqrt(pow(v.x, 2) + pow(v.y, 2)); }

  /**
   * @todo refactor out
   */
  void vec2_normalize(Vector2 * v) {
    double magnitude = vec2_magnitude(*v);
    v->x /= magnitude;
    v->y /= magnitude;
  }

  Vector2 vec2_normalized(Vector2 v) {
    double magnitude = vec2_magnitude(v);
    Vector2 result;
    result.x = v.x / magnitude;
    result.y = v.y / magnitude;
    return result;
  }

  Vector2 vec2_add(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
  }

  Vector2 vec2_sub(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
  }

  Vector2 vec2_mult(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    return result;
  }

  Vector2 vec2_div(Vector2 a, Vector2 b) {
    Vector2 result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    return result;
  }

  Vector2 vec2_scale(Vector2 v, double scale) {
    Vector2 result;
    result.x = v.x * scale;
    result.y = v.y * scale;
    return result;
  }
