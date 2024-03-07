#include "vector.h"
#include "colors.h"
#include "math.h"
#include "parametric.h"

Color3 ray(Vector3 Rsource, Vector3 Rtip, ParametricObject3D objects[], int num_objects);

void drawRay(Vector3 source, Vector3 tip);