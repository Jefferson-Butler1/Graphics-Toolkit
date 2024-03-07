#include "vector.h"
#include "colors.h"
#include "parametric.h"
#include "matrix.h"
#include "rayTrace.h"
#include <stdio.h>

void drawRay(Vector3 source, Vector3 tip){
  G_line(source.x, source.y, tip.x, tip.y);
}

double quadratic_solve(double a, double b, double c) {
	double t1,t2;
	
  double discriminant = (b*b)-4*a*c;
  if(discriminant < 0){
    //prevent imaginary numbers
    return 0;
  }
  printf("a: %f\tb: %f\tc: %f\n",a, b, c);
	t1=(-b+sqrt(discriminant))/(2*a) ;
	t2=(-b-sqrt(discriminant))/(2*a);

  printf("t1: %f\tt2: %f\n",t1, t2);
	
	//note: return the lower of the t values that is positive.
	if(t1>0&&t1<=t2) {
		return t1;
	} else if(t2>0&&t2<=t1) {
		return t2;
	} 
    return 0;
}

Color3 ray(Vector3 Rsource, Vector3 Rtip, ParametricObject3D objects[], int num_objects){

  ParametricObject3D obj;
  Vector3 line,sourceObj, tipObj, lineObj, intersect ;
  Vector3 res = (Vector3){.x=-1}, resrgb;
  for(int i = 0; i < num_objects; i++){
    obj = objects[i];
    //Translate all to obj space
    intersect = (Vector3){0,0,0};
    sourceObj = mat4_mult_point(Rsource, obj.transformI);
    tipObj = mat4_mult_point(Rtip, obj.transformI);
    lineObj = vec3_sub(tipObj,sourceObj);
    line = vec3_sub(Rtip,Rsource);
    
    //FROM BRAYDON
    double A =  (lineObj.x)*(lineObj.x)  + (lineObj.y)*(lineObj.y);
    double B = 2*sourceObj.x*(lineObj.x) + 2*sourceObj.y*(lineObj.y);
    double C = (sourceObj.y*sourceObj.y) +(sourceObj.x*sourceObj.x)-1;
    
    //solve the quadratic equation for finding the intersections of the ray
    double t=quadratic_solve(A,B,C);
        
    //note: return the lower of the t values that is positive.
    intersect.x=Rsource.x+t*(line.x);
    intersect.y=Rsource.y+t*(line.y);
    if(t!=0 && (intersect.x < res.x || res.x <0) ) {
      res = intersect;
      resrgb = (Color3){SPREAD_COL3(obj.material.base_color)};
    }
  }
  if(res.x < 0){
    printf("No intersection\n");
    return color(0,0,0);
  }
  
  G_rgb(resrgb.r,resrgb.g,resrgb.b);
  drawRay(Rsource, res);
  return resrgb;
}