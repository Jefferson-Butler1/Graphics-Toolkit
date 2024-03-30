#include "JeffTools.h"
#include "M3d_matrix_tools.h"
#include <stdio.h>
#include "FPToolkit.h"
#include "math.h"
#include "matrix.h"
#include <assert.h>

// Vector2 quadraticSolve (double a, double b, double c)
// // return number of solutions
// {
//   int n ;
//   double d,ta ;
//   Vector2 result;

//   d = b*b - 4*a*c ;

//   if (d < 0) {
//      n = 0 ;  
//   } else if (d == 0) {
//      ta = 2*a ;
//      result.first = -b / ta ;
//      n = 1 ;
//   } else {
//      d = sqrt(d) ;
//      ta = 2*a ;
//      result.first = (-b + d) / ta ;
//      result.second = (-b - d) / ta ;
//      n = 2 ;
//   }

//   return result ;
// }
// double quadraticSolve(double a, double b, double c) {
// 	double t1,t2;
	
//   double discriminant = (b*b)-4*a*c;
//   if(discriminant < 0){
//     return 0;
//   }
// 	t1=(-b+sqrt(discriminant))/(2*a) ;
// 	t2=(-b-sqrt(discriminant))/(2*a);
	
// 	//note: return the lower of the t values that is positive.
// 	if(t1>0&&t1<=t2) {
// 		return t1;
// 	} else if(t2>0&&t2<=t1) {
// 		return t2;
// 	} 
//   return 0;
// }
double quadraticSolve(double a, double b, double c) {
    double t1,t2;

    t1=(-b+sqrt((b*b)-4*a*c))/(2*a) ;
    t2=(-b-sqrt((b*b)-4*a*c))/(2*a);

    //note: return the lower of the t values that is positive.
    if(t1>0&&t1<=t2) {
        return t1;
    } else if(t2>0&&t2<=t1) {
        return t2;
    } 
    return 0;
}

Vector2 quadSolve(double a, double b, double c){
    double t1,t2;
    t1=(-b+sqrt((b*b)-4*a*c))/(2*a) ;
    t2=(-b-sqrt((b*b)-4*a*c))/(2*a);
    
    return (Vector2){t1, t2};
    
}

/**
 * @brief returns an int which signifies whether it intersected, and places the intersect in the pointer  provided.
 * @param obj The ParametricObj to be intersected
 * @param ray The ray which is intersecting it
 * @param result 
*/
int intersectRayWithObject(ParametricObj obj, Ray ray, Vector3 *result){
    Ray rayObj = {
        .source = mat4_mult_point(ray.source, obj.matrixI),
        .tip    = mat4_mult_point(ray.tip,    obj.matrixI)
    };
    Ray line =  {
        .worldSpace  = vec3_sub(ray   .tip,ray   .source),
        .objectSpace = vec3_sub(rayObj.tip,rayObj.source),
    };

    double t;
    Vector3 intersect;
    switch (obj.type)
    {
    case LINE:
        // printf("Line\n");
        {
            t = -rayObj.source.y/line.objectSpace.y;
            double xAtT = rayObj.source.x + line.objectSpace.x*t;
            if(t<0 || fabs(xAtT) > 1) return NO_INTERSECTION;
        }
        break;
    case CIRCLE:
        // printf("Circle\n");
        {
            double A =  (line.objectSpace.x)*(line.objectSpace.x)  + (line.objectSpace.y)*(line.objectSpace.y);
            double B = 2*rayObj.source.x*(line.objectSpace.x) + 2*rayObj.source.y*(line.objectSpace.y);
            double C = (rayObj.source.y*rayObj.source.y) +(rayObj.source.x*rayObj.source.x)-1;
            
            //solve the quadratic equation for finding the intersections of the ray
            t = quadraticSolve(A,B,C);
        }
        break;
    case HYPERBOLA:
        // printf("Hyperbola\n");
        {
            double A =  (line.objectSpace.x)*(line.objectSpace.x)  - (line.objectSpace.y)*(line.objectSpace.y);
            double B = 2*rayObj.source.x*(line.objectSpace.x) - 2*rayObj.source.y*(line.objectSpace.y);
            double C = (rayObj.source.x*rayObj.source.x) - (rayObj.source.y*rayObj.source.y)-1;
            //solve the quadratic equation for finding the intersections of the ray
            Vector2 tvals = quadSolve(A,B,C);

            //if no value is positive, return no intersection possibly redundate
            if(!(tvals.first > 0) && !(tvals.second > 0)) return NO_INTERSECTION;

            vec2_print(tvals);

            t = fmin(tvals.first, tvals.second);

            Vector3 intersect = vec3_add(rayObj.source, vec3_scale(line.objectSpace, t));
            vec3_print(intersect);
            if(fabs(intersect.y) < 1) break;
            
            t = fmax(tvals.first, tvals.second);
            intersect = vec3_add(rayObj.source, vec3_scale(line.objectSpace, t));
            vec3_print(intersect);
            if(fabs(intersect.y) < 1) break;

            return NO_INTERSECTION;
        }
    default:
        // printf("default\n");
        // return 0;
        break;
    }

    // if(obj.type == HYPERBOLA)    printf("ffft: %f\n", t);
    if(t==0)return NO_INTERSECTION;

    result->x=ray.source.x+t*(line.worldSpace.x);
    result->y=ray.source.y+t*(line.worldSpace.y);

    return 1;
}

/**
 * @param ray the ray to draw
 * @param length set to 0 to disable scaling, otherwise the length of the ray
*/
int drawRay(Ray ray, double length){
    // vec3_print(ray.source);
    // vec3_print(ray.tip);
    if(length){
        Vector3 normal = vec3_scale(vec3_normalized(vec3_sub(ray.tip,ray.source)), length);
        // vec3_print(normal);
        G_line(ray.source.x, ray.source.y, ray.source.x + normal.x, ray.source.y + normal.y) ;
        return 0;
    }
    G_line(ray.source.x, ray.source.y, ray.tip.x, ray.tip.y) ;
    return 0;
}


int printParametricObj(ParametricObj obj){
    printf("Matrix:\n");
    M3d_print_mat(obj.matrix);
    printf("MatrixI:\n");
    M3d_print_mat(obj.matrixI);
    printf("Type:\t%d(CIRCLE = 0,HYPERBOLA = 1, LINE = 2)\n", obj.type);
    return 0;
}

int tValid(ParametricObj obj, double t) { return (obj.tLo < t && t < obj.tHi); }

