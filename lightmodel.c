#include <math.h>
#include <stdio.h>
#include "lightmodel.h"
#include "camera.h"
#include "vector.h"

const double AMBIENT = 0.2;
const double SPECULAR_POWER = 0.8;

//TODO: make specular work, and allow the object color to be passed in
Vector3 phong_lighting(Vector3 position, Vector3 normal, Camera cam, PhongLight* lights, int num_lights){
    Vector3 result = {AMBIENT, AMBIENT, AMBIENT};
    for(int l = 0; l < num_lights; l++){
        PhongLight light = lights[l];
        Vector3 light_dir = vec3_normalized(vec3_sub(light.position, position));
        // return light_dir;
        double dot_prod = vec3_dot_prod(light_dir, normal);
        if(dot_prod > 0){
            // printf("yes\n");
            // Vector3 res = {1, 1, 1};
            // return res;
            Vector3 diffuse = vec3_scale(light.diffuse, dot_prod);
            result = vec3_add(result, diffuse);
            // vec3_print(position);
        }
        // if(dot_prod > 0 || 1){

        //     Vector3 reflection = vec3_normalized(vec3_sub(vec3_scale(normal, 2 * dot_prod), light_dir));
        //     Vector3 view_vec = vec3_normalized(vec3_negated(position));
        //     double spec = pow(vec3_dot_prod(reflection, view_vec), SPECULAR_POWER);
        //     if(spec > 0){
        //         Vector3 specular = vec3_scale(light.specular, spec);
        //         vec3_add(result, specular);
        //     }
        // }
    }
    return result;
}