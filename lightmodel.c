#include <math.h>
#include <stdio.h>
#include "lightmodel.h"
#include "camera.h"
#include "vector.h"

const double AMBIENT = 0.2;
const double SPECULAR_POWER = 64;

//TODO: allow the object color to be passed in
Vector3 phong_lighting(Vector3 position, Vector3 normal, Camera cam, PhongMaterial material, PhongLight* lights, int num_lights){
    Vector3 result = vec3_scale(material.base_color, AMBIENT);
    for(int l = 0; l < num_lights; l++){
        PhongLight light = lights[l];
        Vector3 light_dir = vec3_normalized(vec3_sub(light.position, position));
        double dot_prod = vec3_dot_prod(light_dir, normal);
        if(dot_prod < 0) continue;
        Vector3 diffuse = vec3_mult(vec3_scale(light.diffuse, dot_prod), material.diffuse);
        result = vec3_add(result, diffuse);

        Vector3 reflection = vec3_normalized(vec3_sub(vec3_scale(normal, 2 * dot_prod), light_dir));
        Vector3 view_vec = vec3_normalized(vec3_sub(cam.eye, position));
        double spec = pow(vec3_dot_prod(reflection, view_vec), material.shininess);
        if(spec < 0) continue;
        Vector3 specular = vec3_mult(vec3_scale(light.specular, spec), material.specular);
        result = vec3_add(result, specular);
    }
    return result;
}