#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include "vector.h"
#include "camera.h"

extern const double AMBIENT, SPECULAR_POWER;

typedef struct PhongLight {
    Vector3 position;
    Vector3 diffuse;
    Vector3 specular;
} PhongLight;

/**
 * @brief Calculates the lighting of a given point based on the Phong lightmodel
 * 
 * @param position The world space position of the point
 * @param normal The world space normal vector of the point
 * @param camera The camera to calculate the lightmodel from
 * @param lights An array of PhongLights in world space to use for lighting calculations
 * @param num_lights The number of PhongLights in the array
 * @return Vector3 The color of the point based on the phonglighting
 */
Vector3 phong_lighting(Vector3 position, Vector3 normal, Camera cam, PhongLight* lights, int num_lights);

#endif